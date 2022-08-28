#include <ntddk.h>
#include <intrin.h>
#include "hypervisor_routines.h"
#include "ia32\cpuid.h"
#include "asm\vm_context.h"
#include "ia32\cr.h"
#include "ia32\msr.h"
#include "ia32\vmcs.h"
#include "log.h"
#include "ntapi.h"
#include "ia32\vmcs_encodings.h"
#include "vmcall_handler.h"
#include "interrupt.h"
#include "allocators.h"
#include "asm/vm_intrin.h"
#include "vmexit_handler.h"


#define NON_CANONICIAL_ADDRESS_END 0xFFFF800000000000
#define NON_CANONICIAL_ADDRESS_START 0x0000800000000000


namespace hv 
{
	volatile long vmcs_dump_lock = 0;



	void inject_interruption(unsigned __int32 vector, unsigned __int32 type, unsigned __int32 error_code, bool deliver_error_code)
	{
		__vmentry_interrupt_info interrupt = { 0 };

		interrupt.interruption_type = type;
		interrupt.interrupt_vector = vector;
		interrupt.deliver_error_code = deliver_error_code;
		interrupt.valid = 1;

		if(type == INTERRUPT_TYPE_SOFTWARE_EXCEPTION || type == INTERRUPT_TYPE_PRIVILEGED_SOFTWARE_INTERRUPT || type == INTERRUPT_TYPE_SOFTWARE_INTERRUPT)
			hv::vmwrite<unsigned __int64>(CONTROL_VM_ENTRY_INSTRUCTION_LENGTH, hv::vmread(VM_EXIT_INSTRUCTION_LENGTH));

		if (deliver_error_code == true)
			hv::vmwrite<unsigned __int64>(CONTROL_VM_ENTRY_EXCEPTION_ERROR_CODE, error_code);

		hv::vmwrite<unsigned __int64>(CONTROL_VM_ENTRY_INTERRUPTION_INFORMATION_FIELD, interrupt.all);
	}

	void hard_reset()
	{
		__reset_control_register reset_register;
		reset_register.all = __inbyte(RESET_IO_PORT);

		//
		// Reset CPU bit set, determines type of reset based on:
		//        - System Reset = 0; soft reset by activating INIT# for 16 PCI clocks.
		//        - System Reset = 1; then hard reset by activating PLTRST# and SUS_STAT#.
		//        - System Reset = 1; main power well reset.
		//

		reset_register.reset_cpu = 1;
		reset_register.system_reset = 1;

		__outbyte(RESET_IO_PORT, reset_register.all);
	}

	unsigned __int64 swap_context()
	{
		__nt_kprocess* current_process;

		current_process = (__nt_kprocess*)IoGetCurrentProcess();
		unsigned __int64 current_cr3 = __readcr3();
		unsigned __int64 guest_cr3 = current_process->DirectoryTableBase;

		__writecr3(guest_cr3);
		return current_cr3;
	}

	void restore_context(unsigned __int64 old_cr3)
	{
		__writecr3(old_cr3);
	}

	unsigned __int64 get_system_directory_table_base()
	{
		return ((__nt_kprocess*)PsInitialSystemProcess)->DirectoryTableBase;
	}

	unsigned __int64 vmread(unsigned __int64 vmcs_field)
	{
		unsigned __int64 value;
		__vmx_vmread(vmcs_field, &value);
		return value;
	}

	bool is_address_canonical(unsigned __int64 address)
	{
		if (address < NON_CANONICIAL_ADDRESS_END && address > NON_CANONICIAL_ADDRESS_START)
			return false;
		return true;
	}

	unsigned __int8 get_guest_cpl()
	{
		return vmread(GUEST_CS_SELECTOR) & 3;
	}

	void setMsrBitmap(unsigned __int32 msr, __vcpu* vcpu, bool read, bool write, bool value)
	{
		// 0-1KB: 0-0x1FFF					read
		// 1-2KB: 0xC0000000-0xC0001FFF		read
		// 2-3KB: 0-0x1FFF					write
		// 3-4KB: 0xC0000000-0xC0001FFF		write
		if ((msr > 0x1FFF && msr < 0xC0000000) || msr > 0xC0001FFF)
		{
			LOG_ERROR("Bad msr number");
			return;
		}

		unsigned __int32 bitmapPosition;
		unsigned __int8 bitmapBit;
		unsigned __int8* msrBitmapAddr = vcpu->vcpu_bitmaps.msr_bitmap;

		if (msr >= 0xC0000000)
		{
			msrBitmapAddr += 1024;
			msr -= 0xC0000000;
		}

		bitmapPosition = msr / 8;
		bitmapBit = msr % 8;
		msrBitmapAddr += bitmapPosition;

		if (read)
		{
			if (value)
			{
				*(msrBitmapAddr) |= (1 << bitmapBit);
			}

			else
			{
				*(msrBitmapAddr) &= ~(1 << bitmapBit);
			}
		}
		else if (write)
		{
			msrBitmapAddr += 2048;

			if (value)
			{
				*(msrBitmapAddr) |= (1 << bitmapBit);
			}

			else
			{
				*(msrBitmapAddr) &= ~(1 << bitmapBit);
			}
		}

		//if (msr <= 0x1FFF)
		//{
		//	bitmapPosition = msr / 8;
		//	bitmapBit = msr % 8;

		//	// read access for msr 0x0 to 0x1FFF located at the MSR-bitmap address
		//	if (read)
		//	{
		//		if (value)
		//		{
		//			*(vcpu->vcpu_bitmaps.msr_bitmap + bitmapPosition) |= (1 << bitmapBit);
		//		}

		//		else
		//		{
		//			*(vcpu->vcpu_bitmaps.msr_bitmap + bitmapPosition) &= ~(1 << bitmapBit);
		//		}
		//	}

		//	// write access for msr 0x0 to 0x1FFF located at the MSR-bitmap address plus 1024
		//	else if (write)
		//	{
		//		if (value)
		//		{
		//			*(vcpu->vcpu_bitmaps.msr_bitmap + bitmapPosition + 1024) |= (1 << bitmapBit);
		//		}

		//		else
		//		{
		//			*(vcpu->vcpu_bitmaps.msr_bitmap + bitmapPosition + 1024) &= ~(1 << bitmapBit);
		//		}
		//	}
		//}

		//else if (msr >= 0xC0000000 && msr <= 0xC0001FFF)
		//{
		//	msr -= 0xC0000000;
		//	bitmapPosition = msr / 8;
		//	bitmapBit = msr % 8;

		//	// read access for msr 0xC0000000 to 0xC0001FFF located at the MSR-bitmap address plus 2048
		//	if (read)
		//	{
		//		if (value)
		//		{
		//			*(vcpu->vcpu_bitmaps.msr_bitmap + bitmapPosition + 2048) |= (1 << bitmapBit);
		//		}
		//		else
		//		{
		//			*(vcpu->vcpu_bitmaps.msr_bitmap + bitmapPosition + 2048) &= ~(1 << bitmapBit);
		//		}
		//	}

		//	// write access for msr 0xC0000000 to 0xC0001FFF located at the MSR-bitmap address plus 2048
		//	else if (write)
		//	{
		//		if (value)
		//		{
		//			*(vcpu->vcpu_bitmaps.msr_bitmap + bitmapPosition + 3072) |= (1 << bitmapBit);
		//		}
		//		else
		//		{
		//			*(vcpu->vcpu_bitmaps.msr_bitmap + bitmapPosition + 3072) &= ~(1 << bitmapBit);
		//		}
		//	}
		//}

		//else
		//{
		//	LOG_ERROR("Bad msr number");
		//	return;
		//}
	}

	void setIoBitmap(unsigned __int16 io_port, __vcpu* vcpu, bool value)
	{
		unsigned __int16 bitmap_position;
		unsigned __int8 bitmap_bit;

		// IO ports from 0x8000 to 0xFFFF are encoded in io bitmap b
		if (io_port >= 0x8000)
		{
			io_port -= 0x8000;
			bitmap_position = io_port / 8;
			bitmap_bit = io_port % 8;

			if (value)
			{
				*(vcpu->vcpu_bitmaps.io_bitmap_b + bitmap_position) |= (1 << bitmap_bit);
			}
			else
			{
				*(vcpu->vcpu_bitmaps.io_bitmap_b + bitmap_position) &= ~(1 << bitmap_bit);
			}
		}

		// IO ports from 0 to 0x7fff are encoded in io bitmap b
		else
		{
			bitmap_position = io_port / 8;
			bitmap_bit = io_port % 8;

			if (value)
			{
				*(vcpu->vcpu_bitmaps.io_bitmap_a + bitmap_position) |= (1 << bitmap_bit);
			}
			else
			{
				*(vcpu->vcpu_bitmaps.io_bitmap_a + bitmap_position) &= ~(1 << bitmap_bit);
			}
		}
	}

	unsigned __int64 get_guest_address(__vcpu* vcpu)
	{
		__vmexit_instruction_information2 instruction_information;

		instruction_information.all = vcpu->vmexit_info.instruction_information;

		unsigned __int64 displacement = vcpu->vmexit_info.qualification;

		unsigned __int64 base_value = !instruction_information.base_reg_invalid ? *(&vcpu->vmexit_info.guest_registers->rax - instruction_information.base_reg) : 0;

		unsigned __int64 index_value = !instruction_information.index_reg_invalid ? *(&vcpu->vmexit_info.guest_registers->rax - instruction_information.index_reg) : 0;

		index_value = index_value * (1ULL << instruction_information.scaling);

		unsigned __int64 segment_base = hv::vmread(GUEST_ES_BASE + (instruction_information.segment_register << 1));

		unsigned __int64 guest_address = displacement + base_value + index_value + segment_base;

		return guest_address;
	}

	bool virtualizationSupport()
	{
		__cpuid_info cpuid = { 0 };
		__cpuid(&cpuid.cpu_info[0], 1);
		return cpuid.cpuid_eax_01.feature_information_ecx.virtual_machine_extensions;
	}

	void disableVmxOperation()
	{
		__cr4 cr4 = { 0 };
		__ia32_feature_control_msr feature_msr = { 0 };
		cr4.all = __readcr4();
		cr4.vmx_enable = 0;
		__writecr4(cr4.all);
	}

	void dumpVmcs()
	{
		spinlock::lock(&vmcs_dump_lock);

		DbgPrintEx(DPFLTR_IHVDRIVER_ID, DPFLTR_ERROR_LEVEL,"-----------------------------------VMCS CORE %u DUMP-----------------------------------\r\n",KeGetCurrentProcessorIndex());

		// natural Guest Register State Fields
		LOG_DUMP("GUEST_CR0: 0x%llX", vmread(GUEST_CR0));
		LOG_DUMP("GUEST_CR3: 0x%llX", vmread(GUEST_CR3));
		LOG_DUMP("GUEST_CR4: 0x%llX", vmread(GUEST_CR4));
		LOG_DUMP("GUEST_ES_BASE: 0x%llX", vmread(GUEST_ES_BASE));
		LOG_DUMP("GUEST_CS_BASE: 0x%llX", vmread(GUEST_CS_BASE));
		LOG_DUMP("GUEST_SS_BASE: 0x%llX", vmread(GUEST_SS_BASE));
		LOG_DUMP("GUEST_DS_BASE: 0x%llX", vmread(GUEST_DS_BASE));
		LOG_DUMP("GUEST_FS_BASE: 0x%llX", vmread(GUEST_FS_BASE));
		LOG_DUMP("GUEST_GS_BASE: 0x%llX", vmread(GUEST_GS_BASE));
		LOG_DUMP("GUEST_LDTR_BASE: 0x%llX", vmread(GUEST_LDTR_BASE));
		LOG_DUMP("GUEST_TR_BASE: 0x%llX", vmread(GUEST_TR_BASE));
		LOG_DUMP("GUEST_GDTR_BASE: 0x%llX", vmread(GUEST_GDTR_BASE));
		LOG_DUMP("GUEST_IDTR_BASE: 0x%llX", vmread(GUEST_IDTR_BASE));
		LOG_DUMP("GUEST_DR7: 0x%llX", vmread(GUEST_DR7));
		LOG_DUMP("GUEST_RSP: 0x%llX", vmread(GUEST_RSP));
		LOG_DUMP("GUEST_RIP: 0x%llX", vmread(GUEST_RIP));
		LOG_DUMP("GUEST_RFLAGS: 0x%llX", vmread(GUEST_RFLAGS));
		LOG_DUMP("GUEST_SYSENTER_ESP: 0x%llX", vmread(GUEST_SYSENTER_ESP));
		LOG_DUMP("GUEST_SYSENTER_EIP: 0x%llX", vmread(GUEST_SYSENTER_EIP));
		LOG_DUMP("GUEST_S_CET: 0x%llX", vmread(GUEST_S_CET));
		LOG_DUMP("GUEST_SSP: 0x%llX", vmread(GUEST_SSP));
		LOG_DUMP("GUEST_INTERRUPT_SSP_TABLE_ADDR: 0x%llX", vmread(GUEST_INTERRUPT_SSP_TABLE_ADDR));

		// 64-bit Guest Register State Fields
		LOG_DUMP("GUEST_VMCS_LINK_POINTER: 0x%llX", vmread(GUEST_VMCS_LINK_POINTER));
		LOG_DUMP("GUEST_DEBUG_CONTROL: 0x%llX", vmread(GUEST_DEBUG_CONTROL));
		LOG_DUMP("GUEST_PAT: 0x%llX", vmread(GUEST_PAT));
		LOG_DUMP("GUEST_EFER: 0x%llX", vmread(GUEST_EFER));
		LOG_DUMP("GUEST_PERF_GLOBAL_CONTROL: 0x%llX", vmread(GUEST_PERF_GLOBAL_CONTROL));
		LOG_DUMP("GUEST_PDPTE0: 0x%llX", vmread(GUEST_PDPTE0));
		LOG_DUMP("GUEST_PDPTE1: 0x%llX", vmread(GUEST_PDPTE1));
		LOG_DUMP("GUEST_PDPTE2: 0x%llX", vmread(GUEST_PDPTE2));
		LOG_DUMP("GUEST_PDPTE3: 0x%llX", vmread(GUEST_PDPTE3));
		LOG_DUMP("GUEST_BNDCFGS: 0x%llX", vmread(GUEST_BNDCFGS));
		LOG_DUMP("GUEST_RTIT_CTL: 0x%llX", vmread(GUEST_RTIT_CTL));
		LOG_DUMP("GUEST_PKRS: 0x%llX", vmread(GUEST_PKRS));

		// 32-Bit Guest Register State Fields
		LOG_DUMP("GUEST_ES_LIMIT: 0x%llX", vmread(GUEST_ES_LIMIT));
		LOG_DUMP("GUEST_CS_LIMIT: 0x%llX", vmread(GUEST_CS_LIMIT));
		LOG_DUMP("GUEST_SS_LIMIT: 0x%llX", vmread(GUEST_SS_LIMIT));
		LOG_DUMP("GUEST_DS_LIMIT: 0x%llX", vmread(GUEST_DS_LIMIT));
		LOG_DUMP("GUEST_FS_LIMIT: 0x%llX", vmread(GUEST_FS_LIMIT));
		LOG_DUMP("GUEST_GS_LIMIT: 0x%llX", vmread(GUEST_GS_LIMIT));
		LOG_DUMP("GUEST_LDTR_LIMIT: 0x%llX", vmread(GUEST_LDTR_LIMIT));
		LOG_DUMP("GUEST_TR_LIMIT: 0x%llX", vmread(GUEST_TR_LIMIT));
		LOG_DUMP("GUEST_GDTR_LIMIT: 0x%llX", vmread(GUEST_GDTR_LIMIT));
		LOG_DUMP("GUEST_IDTR_LIMIT: 0x%llX", vmread(GUEST_IDTR_LIMIT));
		LOG_DUMP("GUEST_ES_ACCESS_RIGHTS: 0x%llX", vmread(GUEST_ES_ACCESS_RIGHTS));
		LOG_DUMP("GUEST_CS_ACCESS_RIGHTS: 0x%llX", vmread(GUEST_CS_ACCESS_RIGHTS));
		LOG_DUMP("GUEST_SS_ACCESS_RIGHTS: 0x%llX", vmread(GUEST_SS_ACCESS_RIGHTS));
		LOG_DUMP("GUEST_DS_ACCESS_RIGHTS: 0x%llX", vmread(GUEST_DS_ACCESS_RIGHTS));
		LOG_DUMP("GUEST_FS_ACCESS_RIGHTS: 0x%llX", vmread(GUEST_FS_ACCESS_RIGHTS));
		LOG_DUMP("GUEST_GS_ACCESS_RIGHTS: 0x%llX", vmread(GUEST_GS_ACCESS_RIGHTS));
		LOG_DUMP("GUEST_LDTR_ACCESS_RIGHTS: 0x%llX", vmread(GUEST_LDTR_ACCESS_RIGHTS));
		LOG_DUMP("GUEST_TR_ACCESS_RIGHTS: 0x%llX", vmread(GUEST_TR_ACCESS_RIGHTS));
		LOG_DUMP("GUEST_INTERRUPTIBILITY_STATE: 0x%llX", vmread(GUEST_INTERRUPTIBILITY_STATE));
		LOG_DUMP("GUEST_ACTIVITY_STATE: 0x%llX", vmread(GUEST_ACTIVITY_STATE));
		LOG_DUMP("GUEST_SMBASE: 0x%llX", vmread(GUEST_SMBASE));
		LOG_DUMP("GUEST_SYSENTER_CS: 0x%llX", vmread(GUEST_SYSENTER_CS));
		LOG_DUMP("GUEST_VMX_PREEMPTION_TIMER_VALUE: 0x%llX", vmread(GUEST_VMX_PREEMPTION_TIMER_VALUE));

		// 16-Bit Guest Register State Fields
		LOG_DUMP("GUEST_ES_SELECTOR: 0x%llX", vmread(GUEST_ES_SELECTOR));
		LOG_DUMP("GUEST_CS_SELECTOR: 0x%llX", vmread(GUEST_CS_SELECTOR));
		LOG_DUMP("GUEST_SS_SELECTOR: 0x%llX", vmread(GUEST_SS_SELECTOR));
		LOG_DUMP("GUEST_DS_SELECTOR: 0x%llX", vmread(GUEST_DS_SELECTOR));
		LOG_DUMP("GUEST_FS_SELECTOR: 0x%llX", vmread(GUEST_FS_SELECTOR));
		LOG_DUMP("GUEST_GS_SELECTOR: 0x%llX", vmread(GUEST_GS_SELECTOR));
		LOG_DUMP("GUEST_LDTR_SELECTOR: 0x%llX", vmread(GUEST_LDTR_SELECTOR));
		LOG_DUMP("GUEST_TR_SELECTOR: 0x%llX", vmread(GUEST_TR_SELECTOR));
		LOG_DUMP("GUEST_GUEST_INTERRUPT_STATUS: 0x%llX", vmread(GUEST_GUEST_INTERRUPT_STATUS));
		LOG_DUMP("GUEST_PML_INDEX: 0x%llX", vmread(GUEST_PML_INDEX));

		// Natural Host Register State Fields
		LOG_DUMP("HOST_CR0: 0x%llX", vmread(HOST_CR0));
		LOG_DUMP("HOST_CR3: 0x%llX", vmread(HOST_CR3));
		LOG_DUMP("HOST_CR4: 0x%llX", vmread(HOST_CR4));
		LOG_DUMP("HOST_FS_BASE: 0x%llX", vmread(HOST_FS_BASE));
		LOG_DUMP("HOST_GS_BASE: 0x%llX", vmread(HOST_GS_BASE));
		LOG_DUMP("HOST_TR_BASE: 0x%llX", vmread(HOST_TR_BASE));
		LOG_DUMP("HOST_GDTR_BASE: 0x%llX", vmread(HOST_GDTR_BASE));
		LOG_DUMP("HOST_IDTR_BASE: 0x%llX", vmread(HOST_IDTR_BASE));
		LOG_DUMP("HOST_SYSENTER_ESP: 0x%llX", vmread(HOST_SYSENTER_ESP));
		LOG_DUMP("HOST_SYSENTER_EIP: 0x%llX", vmread(HOST_SYSENTER_EIP));
		LOG_DUMP("HOST_RSP: 0x%llX", vmread(HOST_RSP));
		LOG_DUMP("HOST_RIP: 0x%llX", vmread(HOST_RIP));
		LOG_DUMP("HOST_S_CET: 0x%llX", vmread(HOST_S_CET));
		LOG_DUMP("HOST_SSP: 0x%llX", vmread(HOST_SSP));
		LOG_DUMP("HOST_INTERRUPT_SSP_TABLE_ADDR: 0x%llX", vmread(HOST_INTERRUPT_SSP_TABLE_ADDR));

		// 64-bit Host Register State Fields
		LOG_DUMP("HOST_PAT: 0x%llX", vmread(HOST_PAT));
		LOG_DUMP("HOST_EFER: 0x%llX", vmread(HOST_EFER));
		LOG_DUMP("HOST_PERF_GLOBAL_CTRL: 0x%llX", vmread(HOST_PERF_GLOBAL_CTRL));
		LOG_DUMP("HOST_PKRS: 0x%llX", vmread(HOST_PKRS));

		// 32-bit Host Register State Fields
		LOG_DUMP("HOST_SYSENTER_CS: 0x%llX", vmread(HOST_SYSENTER_CS));

		// 16-bit Host Register State Fields
		LOG_DUMP("HOST_ES_SELECTOR: 0x%llX", vmread(HOST_ES_SELECTOR));
		LOG_DUMP("HOST_CS_SELECTOR: 0x%llX", vmread(HOST_CS_SELECTOR));
		LOG_DUMP("HOST_SS_SELECTOR: 0x%llX", vmread(HOST_SS_SELECTOR));
		LOG_DUMP("HOST_DS_SELECTOR: 0x%llX", vmread(HOST_DS_SELECTOR));
		LOG_DUMP("HOST_FS_SELECTOR: 0x%llX", vmread(HOST_FS_SELECTOR));
		LOG_DUMP("HOST_GS_SELECTOR: 0x%llX", vmread(HOST_GS_SELECTOR));
		LOG_DUMP("HOST_TR_SELECTOR: 0x%llX", vmread(HOST_TR_SELECTOR));

		// Natural Control Register State Fields
		LOG_DUMP("CONTROL_CR0_GUEST_HOST_MASK: 0x%llX", vmread(CONTROL_CR0_GUEST_HOST_MASK));
		LOG_DUMP("CONTROL_CR4_GUEST_HOST_MASK: 0x%llX", vmread(CONTROL_CR4_GUEST_HOST_MASK));
		LOG_DUMP("CONTROL_CR0_READ_SHADOW: 0x%llX", vmread(CONTROL_CR0_READ_SHADOW));
		LOG_DUMP("CONTROL_CR4_READ_SHADOW: 0x%llX", vmread(CONTROL_CR4_READ_SHADOW));
		LOG_DUMP("CONTROL_CR3_TARGET_VALUE_0: 0x%llX", vmread(CONTROL_CR3_TARGET_VALUE_0));
		LOG_DUMP("CONTROL_CR3_TARGET_VALUE_1: 0x%llX", vmread(CONTROL_CR3_TARGET_VALUE_1));
		LOG_DUMP("CONTROL_CR3_TARGET_VALUE_2: 0x%llX", vmread(CONTROL_CR3_TARGET_VALUE_2));
		LOG_DUMP("CONTROL_CR3_TARGET_VALUE_3: 0x%llX", vmread(CONTROL_CR3_TARGET_VALUE_3));

		// 64-bit Control Register State Fields
		LOG_DUMP("CONTROL_BITMAP_IO_A_ADDRESS: 0x%llX", vmread(CONTROL_BITMAP_IO_A_ADDRESS));
		LOG_DUMP("CONTROL_BITMAP_IO_B_ADDRESS: 0x%llX", vmread(CONTROL_BITMAP_IO_B_ADDRESS));
		LOG_DUMP("CONTROL_MSR_BITMAPS_ADDRESS: 0x%llX", vmread(CONTROL_MSR_BITMAPS_ADDRESS));
		LOG_DUMP("CONTROL_VMEXIT_MSR_STORE_ADDRESS: 0x%llX", vmread(CONTROL_VMEXIT_MSR_STORE_ADDRESS));
		LOG_DUMP("CONTROL_VMEXIT_MSR_LOAD_ADDRESS: 0x%llX", vmread(CONTROL_VMEXIT_MSR_LOAD_ADDRESS));
		LOG_DUMP("CONTROL_VMENTER_MSR_LOAD_ADDRESS: 0x%llX", vmread(CONTROL_VMENTER_MSR_LOAD_ADDRESS));
		LOG_DUMP("CONTROL_VMCS_EXECUTIVE_POINTER: 0x%llX", vmread(CONTROL_VMCS_EXECUTIVE_POINTER));
		LOG_DUMP("CONTROL_PML_ADDRESS: 0x%llX", vmread(CONTROL_PML_ADDRESS));
		LOG_DUMP("CONTROL_TSC_OFFSET: 0x%llX", vmread(CONTROL_TSC_OFFSET));
		LOG_DUMP("CONTROL_VIRTUAL_APIC_ADDRESS: 0x%llX", vmread(CONTROL_VIRTUAL_APIC_ADDRESS));
		LOG_DUMP("CONTROL_APIC_ACCESS_ADDRESS: 0x%llX", vmread(CONTROL_APIC_ACCESS_ADDRESS));
		LOG_DUMP("CONTROL_POSTED_INTERRUPT_DESCRIPTOR_ADDRESS: 0x%llX", vmread(CONTROL_POSTED_INTERRUPT_DESCRIPTOR_ADDRESS));
		LOG_DUMP("CONTROL_VM_FUNCTION_CONTROLS: 0x%llX", vmread(CONTROL_VM_FUNCTION_CONTROLS));
		LOG_DUMP("CONTROL_EPT_POINTER: 0x%llX", vmread(CONTROL_EPT_POINTER));
		LOG_DUMP("CONTROL_EOI_EXIT_BITMAP_0: 0x%llX", vmread(CONTROL_EOI_EXIT_BITMAP_0));
		LOG_DUMP("CONTROL_EOI_EXIT_BITMAP_1: 0x%llX", vmread(CONTROL_EOI_EXIT_BITMAP_1));
		LOG_DUMP("CONTROL_EOI_EXIT_BITMAP_2: 0x%llX", vmread(CONTROL_EOI_EXIT_BITMAP_2));
		LOG_DUMP("CONTROL_EOI_EXIT_BITMAP_3: 0x%llX", vmread(CONTROL_EOI_EXIT_BITMAP_3));
		LOG_DUMP("CONTROL_EPTP_LIST_ADDRESS: 0x%llX", vmread(CONTROL_EPTP_LIST_ADDRESS));
		LOG_DUMP("CONTROL_VMREAD_BITMAP_ADDRESS: 0x%llX", vmread(CONTROL_VMREAD_BITMAP_ADDRESS));
		LOG_DUMP("CONTROL_VMWRITE_BITMAP_ADDRESS: 0x%llX", vmread(CONTROL_VMWRITE_BITMAP_ADDRESS));
		LOG_DUMP("CONTROL_VIRTUALIZATION_EXCEPTION_INFORMATION_ADDRESS: 0x%llX", vmread(CONTROL_VIRTUALIZATION_EXCEPTION_INFORMATION_ADDRESS));
		LOG_DUMP("CONTROL_XSS_EXITING_BITMAP: 0x%llX", vmread(CONTROL_XSS_EXITING_BITMAP));
		LOG_DUMP("CONTROL_ENCLS_EXITING_BITMAP: 0x%llX", vmread(CONTROL_ENCLS_EXITING_BITMAP));
		LOG_DUMP("CONTROL_SUB_PAGE_PERMISSION_TABLE_POINTER: 0x%llX", vmread(CONTROL_SUB_PAGE_PERMISSION_TABLE_POINTER));
		LOG_DUMP("CONTROL_TSC_MULTIPLIER: 0x%llX", vmread(CONTROL_TSC_MULTIPLIER));
		LOG_DUMP("CONTROL_ENCLV_EXITING_BITMAP: 0x%llX", vmread(CONTROL_ENCLV_EXITING_BITMAP));

		// 32-bit Control Register State Fields
		LOG_DUMP("CONTROL_PIN_BASED_VM_EXECUTION_CONTROLS: 0x%llX", vmread(CONTROL_PIN_BASED_VM_EXECUTION_CONTROLS));
		LOG_DUMP("CONTROL_PRIMARY_PROCESSOR_BASED_VM_EXECUTION_CONTROLS: 0x%llX", vmread(CONTROL_PRIMARY_PROCESSOR_BASED_VM_EXECUTION_CONTROLS));
		LOG_DUMP("CONTROL_EXCEPTION_BITMAP: 0x%llX", vmread(CONTROL_EXCEPTION_BITMAP));
		LOG_DUMP("CONTROL_PAGE_FAULT_ERROR_CODE_MASK: 0x%llX", vmread(CONTROL_PAGE_FAULT_ERROR_CODE_MASK));
		LOG_DUMP("CONTROL_PAGE_FAULT_ERROR_CODE_MATCH: 0x%llX", vmread(CONTROL_PAGE_FAULT_ERROR_CODE_MATCH));
		LOG_DUMP("CONTROL_CR3_TARGET_COUNT: 0x%llX", vmread(CONTROL_CR3_TARGET_COUNT));
		LOG_DUMP("CONTROL_VM_EXIT_CONTROLS: 0x%llX", vmread(CONTROL_VM_EXIT_CONTROLS));
		LOG_DUMP("CONTROL_VM_EXIT_MSR_STORE_COUNT: 0x%llX", vmread(CONTROL_VM_EXIT_MSR_STORE_COUNT));
		LOG_DUMP("CONTROL_VM_EXIT_MSR_LOAD_COUNT: 0x%llX", vmread(CONTROL_VM_EXIT_MSR_LOAD_COUNT));
		LOG_DUMP("CONTROL_VM_ENTRY_CONTROLS: 0x%llX", vmread(CONTROL_VM_ENTRY_CONTROLS));
		LOG_DUMP("CONTROL_VM_ENTRY_MSR_LOAD_COUNT: 0x%llX", vmread(CONTROL_VM_ENTRY_MSR_LOAD_COUNT));
		LOG_DUMP("CONTROL_VM_ENTRY_INTERRUPTION_INFORMATION_FIELD: 0x%llX", vmread(CONTROL_VM_ENTRY_INTERRUPTION_INFORMATION_FIELD));
		LOG_DUMP("CONTROL_VM_ENTRY_EXCEPTION_ERROR_CODE: 0x%llX", vmread(CONTROL_VM_ENTRY_EXCEPTION_ERROR_CODE));
		LOG_DUMP("CONTROL_VM_ENTRY_INSTRUCTION_LENGTH: 0x%llX", vmread(CONTROL_VM_ENTRY_INSTRUCTION_LENGTH));
		LOG_DUMP("CONTROL_TPR_THRESHOLD: 0x%llX", vmread(CONTROL_TPR_THRESHOLD));
		LOG_DUMP("CONTROL_SECONDARY_PROCESSOR_BASED_VM_EXECUTION_CONTROLS: 0x%llX", vmread(CONTROL_SECONDARY_PROCESSOR_BASED_VM_EXECUTION_CONTROLS));
		LOG_DUMP("CONTROL_PLE_GAP: 0x%llX", vmread(CONTROL_PLE_GAP));
		LOG_DUMP("CONTROL_PLE_WINDOW: 0x%llX", vmread(CONTROL_PLE_WINDOW));

		// 16-bit Control Register State Fields
		LOG_DUMP("CONTROL_VIRTUAL_PROCESSOR_IDENTIFIER: 0x%llX", vmread(CONTROL_VIRTUAL_PROCESSOR_IDENTIFIER));
		LOG_DUMP("CONTROL_POSTED_INTERRUPT_NOTIFICATION_VECTOR: 0x%llX", vmread(CONTROL_POSTED_INTERRUPT_NOTIFICATION_VECTOR));
		LOG_DUMP("CONTROL_EPTP_INDEX: 0x%llX", vmread(CONTROL_EPTP_INDEX));

		// Natural Read only Register State Fields
		LOG_DUMP("EXIT_QUALIFICATION: 0x%llX", vmread(EXIT_QUALIFICATION));
		LOG_DUMP("IO_RCX: 0x%llX", vmread(IO_RCX));
		LOG_DUMP("IO_RSI: 0x%llX", vmread(IO_RSI));
		LOG_DUMP("IO_RDI: 0x%llX", vmread(IO_RDI));
		LOG_DUMP("IO_RIP: 0x%llX", vmread(IO_RIP));
		LOG_DUMP("GUEST_LINEAR_ADDRESS: 0x%llX", vmread(GUEST_LINEAR_ADDRESS));

		// 64-bit Read only Register State Fields
		LOG_DUMP("GUEST_PHYSICAL_ADDRESS: 0x%llX", vmread(GUEST_PHYSICAL_ADDRESS));

		// 32-bit Read only Register State Fields
		LOG_DUMP("VM_INSTRUCTION_ERROR: 0x%llX", vmread(VM_INSTRUCTION_ERROR));
		LOG_DUMP("EXIT_REASON: 0x%llX", vmread(EXIT_REASON));
		LOG_DUMP("VM_EXIT_INTERRUPTION_INFORMATION: 0x%llX", vmread(VM_EXIT_INTERRUPTION_INFORMATION));
		LOG_DUMP("VM_EXIT_INTERRUPTION_ERROR_CODE: 0x%llX", vmread(VM_EXIT_INTERRUPTION_ERROR_CODE));
		LOG_DUMP("IDT_VECTORING_INFORMATION_FIELD: 0x%llX", vmread(IDT_VECTORING_INFORMATION_FIELD));
		LOG_DUMP("IDT_VECTORING_ERROR_CODE: 0x%llX", vmread(IDT_VECTORING_ERROR_CODE));
		LOG_DUMP("VM_EXIT_INSTRUCTION_LENGTH: 0x%llX", vmread(VM_EXIT_INSTRUCTION_LENGTH));
		LOG_DUMP("VM_EXIT_INSTRUCTION_INFORMATION: 0x%llX", vmread(VM_EXIT_INSTRUCTION_INFORMATION));

		DbgPrintEx(DPFLTR_IHVDRIVER_ID, DPFLTR_ERROR_LEVEL, "-----------------------------------VMCS CORE %u DUMP-----------------------------------\r\n", KeGetCurrentProcessorIndex());

		spinlock::unlock(&vmcs_dump_lock);
	}
}