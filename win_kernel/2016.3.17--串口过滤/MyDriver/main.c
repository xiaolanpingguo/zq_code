#include "ComCap.h"


#define	DEVICE_NAME			L"\\Device\\MyDriver"
#define LINK_NAME			L"\\DosDevices\\MyDriver"
#define LINK_GLOBAL_NAME	L"\\DosDevices\\Global\\MyDriver"


VOID DriverUnload(PDRIVER_OBJECT pDriverObj)
{
	ULONG i;
	LARGE_INTEGER interval;

	//首先解除绑定
	for (i = 0; i < CCP_MAX_COM_ID; ++i)
	{
		if (s_nextobj[i] != NULL)
			IoDeleteDevice(s_nextobj[i]);
	}

	//睡眠5秒，等待所有的IRP处理结束
	interval.QuadPart = (5 * 1000 * DELAY_ONE_MILLISECOND);
	KeDelayExecutionThread(KernelMode, FALSE, &interval);

	//删除过滤设备
	for (i = 0; i < CCP_MAX_COM_ID; ++i)
	{
		if (s_fltobj[i] != NULL)
			IoDeleteDevice(s_fltobj[i]);
	}

	//删除符号连接和设备
	UNICODE_STRING strLink;
	RtlInitUnicodeString(&strLink, LINK_NAME);
	IoDeleteSymbolicLink(&strLink);
	IoDeleteDevice(pDriverObj->DeviceObject);
	DbgPrint("DriverUnload Succed!\n");
}

NTSTATUS ccpDispatch(PDEVICE_OBJECT device, PIRP irp)
{
	PIO_STACK_LOCATION irpsp = IoGetCurrentIrpStackLocation(irp);
	NTSTATUS status;
	ULONG i, j;

	//遍历所有设备
	for (i = 0; i < CCP_MAX_COM_ID; ++i)
	{
		if (s_fltobj[i] == device)
		{
			//所有的电源操作全部通过
			if (irpsp->MajorFunction == IRP_MJ_POWER)
			{
				//直接发送，然后返回说一句被处理了
				PoStartNextPowerIrp(irp);
				IoSkipCurrentIrpStackLocation(irp);
				return PoCallDriver(device, irp);
			}

			//然后过滤写请求
			if (irpsp->MajorFunction == IRP_MJ_WRITE)
			{
				//先获得长度
				ULONG len = irpsp->Parameters.Write.Length;

				//然后获得缓冲区
				PUCHAR buf = NULL;
				if (irp->MdlAddress != NULL)
					buf = (PUCHAR)MmGetSystemAddressForMdlSafe(irp->MdlAddress, NormalPagePriority);
				else
					buf = (PUCHAR)irp->UserBuffer;

				if (buf == NULL)
					buf = (PUCHAR)irp->AssociatedIrp.SystemBuffer;

				//打印内容
				for (j = 0; j < len; ++j)
				{
					DbgPrint("comcap: Send Data: %2x\n", buf[j]);
				}
			}

			//这些请求直接下发执行即可，没有禁止它或者改变它
			IoSkipCurrentIrpStackLocation(irp);
			return IoCallDriver(s_nextobj[i], irp);
		}
	}

	//如果没在绑定的设备中，就是有问题的，直接返回参数错误
	irp->IoStatus.Information = 0;
	irp->IoStatus.Status = STATUS_INVALID_PARAMETER;
	IoCompleteRequest(irp, IO_NO_INCREMENT);
	return STATUS_SUCCESS;
}

NTSTATUS DriverEntry(PDRIVER_OBJECT pDriverObj, PUNICODE_STRING pRegistryString)
{
	UNICODE_STRING ustrLinkName;
	UNICODE_STRING ustrDevName;
	PDEVICE_OBJECT pDevObj;
	NTSTATUS status = STATUS_SUCCESS;

	//设置分发函数和卸载例程
	size_t i;
	for (i = 0; i < IRP_MJ_MAXIMUM_FUNCTION; ++i)
	{
		pDriverObj->MajorFunction[i] = ccpDispatch;
	}
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

	// 绑定所有的串口。
	ccpAttachAllComs(pDriverObj);

	DbgPrint("DriverEntry Succeed!\n");
	
	//返回加载驱动的状态，如果返回失败，驱动讲被清除出内核空间
	return STATUS_SUCCESS;
}