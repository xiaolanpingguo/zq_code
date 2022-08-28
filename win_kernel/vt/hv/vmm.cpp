#include <ntddk.h>
#include <intrin.h>
#include "common.h"
#include "ia32\cpuid.h"
#include "asm\vm_context.h"
#include "ia32\cr.h"
#include "ia32\msr.h"
#include "ia32\vmcs.h"
#include "log.h"
#include "ntapi.h"
#include "ia32\vmcs_encodings.h"
#include "allocators.h"


static void dpcBroadcastInitializeGuest(KDPC* Dpc, PVOID DeferredContext, PVOID SystemArgument1, PVOID SystemArgument2)
{
	UNREFERENCED_PARAMETER(DeferredContext);
	UNREFERENCED_PARAMETER(Dpc);

	vmxSaveState();

	// wait for all DPCs to synchronize at this point
	KeSignalCallDpcSynchronize(SystemArgument2);

	// mark the DPC as being complete
	KeSignalCallDpcDone(SystemArgument1);
}

void freeVmmContext()
{
	if (g_vmm_context != nullptr)
	{
		// POOL MANAGER
		if (g_vmm_context->pool_manager != nullptr)
		{
			PoolManager::uninitialize();
			freePool(g_vmm_context->pool_manager);
		}

		// EPT STATE
		if (g_vmm_context->ept_state != nullptr)
		{
			// EPT POINTER
			if (g_vmm_context->ept_state->ept_pointer != nullptr)
			{
				freePool(g_vmm_context->ept_state->ept_pointer);
			}
			// EPT PAGE TABLE
			if (g_vmm_context->ept_state->ept_page_table != nullptr)
			{
				freeContignousMemory(g_vmm_context->ept_state->ept_page_table);

			}
			freePool(g_vmm_context->ept_state);
		}

		// VCPU TABLE
		if (g_vmm_context->vcpu_table != nullptr)
		{
			for (unsigned int i = 0; i < g_vmm_context->processor_count; i++)
			{
				// VCPU
				if (g_vmm_context->vcpu_table[i] != nullptr)
				{
					// VCPU VMXON REGION
					if (g_vmm_context->vcpu_table[i]->vmxon != nullptr)
					{
						freeContignousMemory(g_vmm_context->vcpu_table[i]->vmxon);
					}

					// VCPU VMCS REGION
					if (g_vmm_context->vcpu_table[i]->vmcs != nullptr)
					{
						freeContignousMemory(g_vmm_context->vcpu_table[i]->vmcs);
					}

					// VCPU VMM STACK
					if (g_vmm_context->vcpu_table[i]->vmm_stack != nullptr)
					{
						freePool(g_vmm_context->vcpu_table[i]->vmm_stack);
					}

					// MSR BITMAP
					if (g_vmm_context->vcpu_table[i]->vcpu_bitmaps.msr_bitmap != nullptr)
					{
						freePool(g_vmm_context->vcpu_table[i]->vcpu_bitmaps.msr_bitmap);
					}

					// IO BITMAP A
					if (g_vmm_context->vcpu_table[i]->vcpu_bitmaps.io_bitmap_a != nullptr)
					{
						freePool(g_vmm_context->vcpu_table[i]->vcpu_bitmaps.io_bitmap_a);
					}

					// IO BITMAP B
					if (g_vmm_context->vcpu_table[i]->vcpu_bitmaps.io_bitmap_b != nullptr)
					{
						freePool(g_vmm_context->vcpu_table[i]->vcpu_bitmaps.io_bitmap_b);
					}

					freePool(g_vmm_context->vcpu_table[i]);
				}
			}
			freePool(g_vmm_context->vcpu_table);
		}

		freePool(g_vmm_context);
	}

	g_vmm_context = 0;
}

static bool initVmcs(__vcpu* vcpu)
{
	vcpu->vmcs = allocateContignousMemory<__vmcs*>(PAGE_SIZE);
	if (vcpu->vmcs == NULL)
	{
		LOG_ERROR("Vmcs structure could not be allocated");
		return false;
	}
	RtlSecureZeroMemory(vcpu->vmcs, PAGE_SIZE);

	vcpu->vmcs_physical = MmGetPhysicalAddress(vcpu->vmcs).QuadPart;
	if (vcpu->vmcs_physical == NULL)
	{
		LOG_ERROR("Could not get physical address of vmcs");
		return false;
	}

	__vmx_basic_msr vmx_basic = { 0 };
	vmx_basic.all = __readmsr(IA32_VMX_BASIC);
	vcpu->vmcs->header.revision_identifier = vmx_basic.vmcs_revision_identifier;

	// indicates if it's shadow vmcs or not
	vcpu->vmcs->header.shadow_vmcs_indicator = 0;

	return true;
}

// allocate whole vmm context, build mtrr map, initalize pool manager and initialize ept structure 
static bool allocateVmContext()
{
	// allocate Nonpaged memory for vm global context structure
	g_vmm_context = allocatePool<__vmm_context>();
	if (g_vmm_context == nullptr) 
	{
		LOG_ERROR("g_vmm_context could not be allocated");
		return false;
	}
	RtlSecureZeroMemory(g_vmm_context, sizeof(__vmm_context));

	// allocate virtual cpu context for every logical core
	g_vmm_context->processor_count = KeQueryActiveProcessorCountEx(ALL_PROCESSOR_GROUPS);
	g_vmm_context->vcpu_table = allocatePool<__vcpu**>(sizeof(__vcpu*) * (g_vmm_context->processor_count));
	if (g_vmm_context->vcpu_table == nullptr)
	{
		LOG_ERROR("vcpu_table could not be allocated");
		return false;
	}
	RtlSecureZeroMemory(g_vmm_context->vcpu_table, sizeof(__vcpu*) * (g_vmm_context->processor_count));

	// allocate ept state structure
	g_vmm_context->ept_state = allocatePool<__ept_state>();
	if (g_vmm_context->ept_state == nullptr)
	{
		LOG_ERROR("ept state could not be allocated");
		return false;
	}
	RtlSecureZeroMemory(g_vmm_context->ept_state, sizeof(__ept_state));

	InitializeListHead(&g_vmm_context->ept_state->hooked_page_list);

	// build mtrr map for physcial memory caching informations
	ept::buildMtrrMap();

	if (!PoolManager::initialize())
	{
		return false;
	}

	// initialize ept structure
	if (!ept::initialize())
	{
		return false;
	}

	g_vmm_context->hv_presence = true;

	__cpuid_info cpuid_reg = { 0 };
	__cpuid((int*)&cpuid_reg.eax, 0);
	g_vmm_context->highest_basic_leaf = cpuid_reg.eax;

	return true;
}

static bool initcpu(__vcpu*& vcpu)
{
	vcpu = allocatePool<__vcpu>();
	if (vcpu == nullptr)
	{
		LOG_ERROR("vcpu structure could not be allocated");
		return false;
	}
	RtlSecureZeroMemory(vcpu, sizeof(__vcpu));

	vcpu->vmm_stack = allocatePool<void*>(VMM_STACK_SIZE);
	if (vcpu->vmm_stack == nullptr)
	{
		LOG_ERROR("vmm stack could not be allocated");
		return false;
	}
	RtlSecureZeroMemory(vcpu->vmm_stack, VMM_STACK_SIZE);

	vcpu->vcpu_bitmaps.msr_bitmap = allocatePool<unsigned __int8*>(PAGE_SIZE);
	if (vcpu->vcpu_bitmaps.msr_bitmap == nullptr)
	{
		LOG_ERROR("msr bitmap could not be allocated");
		return false;
	}
	RtlSecureZeroMemory(vcpu->vcpu_bitmaps.msr_bitmap, PAGE_SIZE);
	vcpu->vcpu_bitmaps.msr_bitmap_physical = MmGetPhysicalAddress(vcpu->vcpu_bitmaps.msr_bitmap).QuadPart;

	vcpu->vcpu_bitmaps.io_bitmap_a = allocatePool<unsigned __int8*>(PAGE_SIZE);
	if (vcpu->vcpu_bitmaps.io_bitmap_a == nullptr)
	{
		LOG_ERROR("io bitmap a could not be allocated");
		return false;
	}
	RtlSecureZeroMemory(vcpu->vcpu_bitmaps.io_bitmap_a, PAGE_SIZE);
	vcpu->vcpu_bitmaps.io_bitmap_a_physical = MmGetPhysicalAddress(vcpu->vcpu_bitmaps.io_bitmap_a).QuadPart;

	vcpu->vcpu_bitmaps.io_bitmap_b = allocatePool<unsigned __int8*>(PAGE_SIZE);
	if (vcpu->vcpu_bitmaps.io_bitmap_b == nullptr)
	{
		LOG_ERROR("io bitmap b could not be allocated");
		return false;
	}
	RtlSecureZeroMemory(vcpu->vcpu_bitmaps.io_bitmap_b, PAGE_SIZE);
	vcpu->vcpu_bitmaps.io_bitmap_b_physical = MmGetPhysicalAddress(vcpu->vcpu_bitmaps.io_bitmap_b).QuadPart;

	LOG_INFO("vcpu entry allocated successfully at %llX", vcpu);

	return true;
}

static bool initVmxon(__vcpu* vcpu)
{
	__vmx_basic_msr vmx_basic = { 0 };
	vmx_basic.all = __readmsr(IA32_VMX_BASIC);
	if (vmx_basic.vmxon_region_size > PAGE_SIZE)
	{
		vcpu->vmxon = allocateContignousMemory<__vmcs*>(PAGE_SIZE);
	}
	else
	{
		vcpu->vmxon = allocateContignousMemory<__vmcs*>(vmx_basic.vmxon_region_size);
	}

	if (vcpu->vmxon == nullptr)
	{
		LOG_ERROR("vmxon could not be allocated");
		return false;
	}

	vcpu->vmxon_physical = MmGetPhysicalAddress(vcpu->vmxon).QuadPart;
	if (vcpu->vmxon_physical == 0)
	{
		LOG_ERROR("Could not get vmxon physical address");
		return false;
	}

	RtlSecureZeroMemory(vcpu->vmxon, PAGE_SIZE);
	vcpu->vmxon->header.all = vmx_basic.vmcs_revision_identifier;
	vcpu->vmxon->header.shadow_vmcs_indicator = 0;

	return true;
}

// adjust cr4 and cr0 for turning on vmx
static void adjustControlRegisters()
{
	__cr4 cr4;
	__cr0 cr0;
	__cr_fixed cr_fixed;

	cr_fixed.all = __readmsr(IA32_VMX_CR0_FIXED0);
	cr0.all = __readcr0();
	cr0.all |= cr_fixed.split.low;
	cr_fixed.all = __readmsr(IA32_VMX_CR0_FIXED1);
	cr0.all &= cr_fixed.split.low;
	__writecr0(cr0.all);

	cr_fixed.all = __readmsr(IA32_VMX_CR4_FIXED0);
	cr4.all = __readcr4();
	cr4.all |= cr_fixed.split.low;
	cr_fixed.all = __readmsr(IA32_VMX_CR4_FIXED1);
	cr4.all &= cr_fixed.split.low;
	__writecr4(cr4.all);

	__ia32_feature_control_msr feature_msr = { 0 };
	feature_msr.all = __readmsr(IA32_FEATURE_CONTROL);
	if (feature_msr.lock == 0) 
	{
		feature_msr.vmxon_outside_smx = 1;
		feature_msr.lock = 1;

		__writemsr(IA32_FEATURE_CONTROL, feature_msr.all);
	}
}

// initialize logical core and launch virtual machine managed by current vmcs
void initLogicalProcessor(void* guest_rsp)
{
	ULONG processorNumber = KeGetCurrentProcessorNumber();

	__vcpu* vcpu = g_vmm_context->vcpu_table[processorNumber];

	adjustControlRegisters();

	if (__vmx_on(&vcpu->vmxon_physical)) 
	{
		LOG_ERROR("Failed to put vcpu %d into VMX operation.\n", processorNumber);
		return;
	}

	vcpu->vcpu_status.vmx_on = true;
	LOG_INFO("vcpu %d is now in VMX operation.\n", processorNumber);

	fillVmcs(vcpu, guest_rsp);
	vcpu->vcpu_status.vmm_launched = true;

	__vmx_vmlaunch();

	// we should never get here
	LOG_ERROR("Vmlaunch failed");
	ASSERT(FALSE);
	vcpu->vcpu_status.vmm_launched = false;
	vcpu->vcpu_status.vmx_on = false;
	__vmx_off();
}

bool vmmInit()
{
	if (!allocateVmContext())
	{
		return false;
	}

	// Initalize vcpu for each logical core
	for (unsigned int iter = 0; iter < g_vmm_context->processor_count; iter++) 
	{
		if (!initcpu(g_vmm_context->vcpu_table[iter]))
		{
			return false;
		}

		if (!initVmxon(g_vmm_context->vcpu_table[iter]))
		{
			return false;
		}

		if (!initVmcs(g_vmm_context->vcpu_table[iter]))
		{
			return false;
		}
	}

	// Call derefered procedure call (DPC) to fill vmcs and launch vmm for every logical core
	KeGenericCallDpc(dpcBroadcastInitializeGuest, 0);
	return true;
}