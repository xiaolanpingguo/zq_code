#include "FileOperatiom.h"


#define	DEVICE_NAME			L"\\Device\\MyDriver"
#define LINK_NAME			L"\\DosDevices\\MyDriver"
#define LINK_GLOBAL_NAME	L"\\DosDevices\\Global\\MyDriver"


VOID DriverUnload(PDRIVER_OBJECT pDriverObj)
{
	DbgPrint("DriverUnload!\n");

	//删除符号连接和设备
	UNICODE_STRING strLink;
	RtlInitUnicodeString(&strLink, LINK_NAME);
	IoDeleteSymbolicLink(&strLink);
	IoDeleteDevice(pDriverObj->DeviceObject);
}

//IRP_MJ_CREATE对应的处理例程，一般不用管它
NTSTATUS DispatchCreate(PDEVICE_OBJECT pDevObj, PIRP pIrp)
{
	pIrp->IoStatus.Status = STATUS_SUCCESS;
	pIrp->IoStatus.Information = 0;
	IoCompleteRequest(pIrp, IO_NO_INCREMENT);
	return STATUS_SUCCESS;
}

//IRP_MJ_CLOSE对应的处理例程，一般不用管它
NTSTATUS DispatchClose(PDEVICE_OBJECT pDevObj, PIRP pIrp)
{
	pIrp->IoStatus.Status = STATUS_SUCCESS;
	pIrp->IoStatus.Information = 0;
	IoCompleteRequest(pIrp, IO_NO_INCREMENT);
	return STATUS_SUCCESS;
}

//IRP_MJ_DEVICE_CONTROL对应的处理例程，驱动最重要的函数之一，一般走正常途径调用驱动功能的程序，都会经过这个函数
NTSTATUS DispatchIoctl(PDEVICE_OBJECT pDevObj, PIRP pIrp)
{
	NTSTATUS status = STATUS_INVALID_DEVICE_REQUEST;
	PIO_STACK_LOCATION pIrpStack;
	ULONG uIoControlCode;
	PVOID pIoBuffer;
	ULONG uInSize;
	ULONG uOutSize;

	//获得IRP里的关键数据
	pIrpStack = IoGetCurrentIrpStackLocation(pIrp);

	//这个就是传说中的控制码
	uIoControlCode = pIrpStack->Parameters.DeviceIoControl.IoControlCode;

	//输入和输出的缓冲区（DeviceIoControl的InBuffer和OutBuffer都是它）
	pIoBuffer = pIrp->AssociatedIrp.SystemBuffer;

	//EXE发送传入数据的BUFFER长度（DeviceIoControl的nInBufferSize）
	uInSize = pIrpStack->Parameters.DeviceIoControl.InputBufferLength;

	//EXE接收传出数据的BUFFER长度（DeviceIoControl的nOutBufferSize）
	uOutSize = pIrpStack->Parameters.DeviceIoControl.OutputBufferLength;
	switch (uIoControlCode)
	{
	default:
		break;
	}

	//这里设定DeviceIoControl的*lpBytesReturned的值（如果通信失败则返回0长度）
	if (status == STATUS_SUCCESS)
	{
		pIrp->IoStatus.Information = uOutSize;
	}
	else
	{
		pIrp->IoStatus.Information = 0;
	}

	//这里设定DeviceIoControl的返回值是成功还是失败
	pIrp->IoStatus.Status = status;
	IoCompleteRequest(pIrp, IO_NO_INCREMENT);

	return status;
}

NTSTATUS DriverEntry(PDRIVER_OBJECT pDriverObj, PUNICODE_STRING pRegistryString)
{
	DbgPrint("DriverEntry!\n");
	UNICODE_STRING ustrLinkName;
	UNICODE_STRING ustrDevName;
	PDEVICE_OBJECT pDevObj;
	NTSTATUS status = STATUS_SUCCESS;

	//设置分发函数和卸载例程
	pDriverObj->MajorFunction[IRP_MJ_CREATE] = DispatchCreate;
	pDriverObj->MajorFunction[IRP_MJ_CLOSE] = DispatchClose;
	pDriverObj->MajorFunction[IRP_MJ_DEVICE_CONTROL] = DispatchIoctl;
	pDriverObj->DriverUnload = DriverUnload;

	//创建一个设备对象
	RtlInitUnicodeString(&ustrDevName, DEVICE_NAME);
	status = IoCreateDevice(pDriverObj, 0, &ustrDevName, FILE_DEVICE_UNKNOWN, 0, FALSE, &pDevObj);
	if (!NT_SUCCESS(status))
	{
		return status;
	}
	else
	{
		RtlInitUnicodeString(&ustrLinkName, LINK_NAME);
	}

	//创建符号连接
	status = IoCreateSymbolicLink(&ustrLinkName, &ustrDevName);
	if (!NT_SUCCESS(status))
	{
		IoDeleteDevice(pDevObj);
		return status;
	}

	if (FALSE == ZwCopyFile(L"C:\\3.txt", L"D:\\1.txt"))
		DbgPrint("ZwCopyFile Faild!\n");
	NTSTATUS st;
	st = ZwDeleteFileFolder(L"D:\\1.txt");
	if (st != STATUS_SUCCESS)
	{
		DbgPrint("ZwDeleteFileFolder Faild:%08x\n", st);
	}
	if (STATUS_SUCCESS != ZwRenameFile(L"D:\\4.txt", L"D:\\3.txt"))
		DbgPrint("ZwRenameFile Faild!\n");
	DbgPrint("FileSize=%ld\n", GetFileSize(L"D:\\1.txt"));
	DbgPrint("Count=%ld\n", SearchDirectory("C:\\2"));
	
	//返回加载驱动的状态，如果返回失败，驱动讲被清除出内核空间
	return STATUS_SUCCESS;
}