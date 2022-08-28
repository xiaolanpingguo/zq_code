#include <ntddk.h>
#include <intrin.h>
#include "log.h"
#include "ntapi.h"
#include "hypervisor_routines.h"
#include "hypervisor_gateway.h"
#include "vmm.h"

#define IOCTL_POOL_MANAGER_ALLOCATE CTL_CODE(FILE_DEVICE_UNKNOWN, 0x900, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)

__vmm_context* g_vmm_context = 0;

 VOID driverUnload(PDRIVER_OBJECT driver_object)
 {
	 LOG_INFO("--driverUnload--\n");
	 UNICODE_STRING dos_device_name;
	 if(g_vmm_context != NULL)
	 {
		 if (g_vmm_context->vcpu_table[0]->vcpu_status.vmm_launched)
		 {
			 hvgt::ept_unhook();
			 hvgt::vmoff();
		 }
	 }

	 hv::disableVmxOperation();
	 freeVmmContext();

	 RtlInitUnicodeString(&dos_device_name, L"\\DosDevices\\xyhv");
	 IoDeleteSymbolicLink(&dos_device_name);
	 IoDeleteDevice(driver_object->DeviceObject);
 }

 NTSTATUS driverCreateClose(_In_ PDEVICE_OBJECT device_object, _In_ PIRP irp)
 {
	 UNREFERENCED_PARAMETER(device_object);

	 irp->IoStatus.Status = STATUS_SUCCESS;
	 irp->IoStatus.Information = 0;

	 IoCompleteRequest(irp, IO_NO_INCREMENT);

	 return STATUS_SUCCESS;
 }

 NTSTATUS driverIoctlDispatcher(_In_ PDEVICE_OBJECT device_object, _In_ PIRP irp)
 {
	 UNREFERENCED_PARAMETER(device_object);
	 PIO_STACK_LOCATION stack = IoGetCurrentIrpStackLocation(irp);
	 NTSTATUS status = STATUS_SUCCESS;

	 switch (stack->Parameters.DeviceIoControl.IoControlCode)
	 {
		 // Used by hypervisor control driver to perform allocations
		 case IOCTL_POOL_MANAGER_ALLOCATE:
		 {
			 status = PoolManager::performAllocation();
			 break;
		 }
	 }

	 irp->IoStatus.Status = status;
	 irp->IoStatus.Information = 0;

	 IoCompleteRequest(irp, IO_NO_INCREMENT);
	 return status;
 }

extern "C" NTSTATUS DriverEntry(PDRIVER_OBJECT driver_object, PCUNICODE_STRING reg) 
{
	UNREFERENCED_PARAMETER(reg);

	NTSTATUS status = STATUS_SUCCESS;
	PDEVICE_OBJECT device_object = NULL;
	UNICODE_STRING driver_name, dos_device_name;

	RtlInitUnicodeString(&driver_name, L"\\Device\\xyhv");
	RtlInitUnicodeString(&dos_device_name, L"\\DosDevices\\xyhv");

	status = IoCreateDevice(driver_object, 0, &driver_name, FILE_DEVICE_UNKNOWN, FILE_DEVICE_SECURE_OPEN, FALSE, &device_object);
	if (status == STATUS_SUCCESS)
	{
		driver_object->MajorFunction[IRP_MJ_CLOSE] = driverCreateClose;
		driver_object->MajorFunction[IRP_MJ_CREATE] = driverCreateClose;
		driver_object->MajorFunction[IRP_MJ_DEVICE_CONTROL] = driverIoctlDispatcher;

		driver_object->DriverUnload = driverUnload;
		driver_object->Flags |= DO_BUFFERED_IO;
		IoCreateSymbolicLink(&dos_device_name, &driver_name);
	}

	// check if our cpu support virtualization
	if (!hv::virtualizationSupport()) 
	{
		LOG_ERROR("VMX operation is not supported on this processor.\n");
		return STATUS_FAILED_DRIVER_ENTRY;
	}

	// initialize and start virtual machine, if it fails turn off vmx and deallocate all structures
	if(!vmmInit())
	{
		hv::disableVmxOperation();
		freeVmmContext();
		LOG_ERROR("Vmm initialization failed");
		return STATUS_FAILED_DRIVER_ENTRY;
	}

	return status;
}