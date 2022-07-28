#ifndef COM_CAP_H
#define COM_CAP_H

#include <ntddk.h>
#include <ntstrsafe.h>


#define CCP_MAX_COM_ID 32
#define DELAY_ONE_MICROSECOND  (-10)
#define DELAY_ONE_MILLISECOND (DELAY_ONE_MICROSECOND*1000)
#define DELAY_ONE_SECOND (DELAY_ONE_MILLISECOND*1000)


// 过滤设备和真实设备
static PDEVICE_OBJECT s_fltobj[CCP_MAX_COM_ID] = { 0 };
static PDEVICE_OBJECT s_nextobj[CCP_MAX_COM_ID] = { 0 };

// 通过设备名字获得一个端口设备
PDEVICE_OBJECT ccpOpenCom(ULONG id)
{
	UNICODE_STRING name_str;
	static WCHAR name[32] = { 0 };
	PFILE_OBJECT fileobj = NULL;
	PDEVICE_OBJECT devobj = NULL;
	NTSTATUS status;

	// 输入字符串
	memset(name, 0, sizeof(WCHAR) * 32);
	RtlStringCchPrintfW(name, 32, L"\\Device\\Serial%d", id);
	RtlInitUnicodeString(&name_str, name);

	// 由设置名字得到设备对象
	status = IoGetDeviceObjectPointer(&name_str, FILE_ALL_ACCESS, &fileobj, &devobj);

	//如果成功，需要把这个文件对象解除引用，否则会引起内存泄漏
	if (status == STATUS_SUCCESS)
		ObDereferenceObject(fileobj);

	return devobj;
}

// 生成过滤设备并绑定
NTSTATUS ccpAttachDevice(PDRIVER_OBJECT pDriverObj, PDEVICE_OBJECT pOldObj, PDEVICE_OBJECT* pFltObj, PDEVICE_OBJECT* pNext)
{
	NTSTATUS status;
	PDEVICE_OBJECT topdev;

	//生成设备
	status = IoCreateDevice(pDriverObj,//本驱动对象
		0,//设备扩展，这里传0即可
		NULL,//过滤设备名字，一般不需要名字
		pOldObj->DeviceType,//设备类型，保持和被绑定的设备类型一致即可
		0,//设备特征
		FALSE,
		pFltObj//过滤设备
		);
	if (status != STATUS_SUCCESS)
		return status;

	//绑定设备之前，需要把这个设备对象的多个子域设置成和要绑定
	//的目标对象一致，包括特征和标志
	//拷贝重要标志位
	if (pOldObj->Flags & DO_BUFFERED_IO)
		(*pFltObj)->Flags |= DO_BUFFERED_IO;
	if (pOldObj->Flags & DO_DIRECT_IO)
		(*pFltObj)->Flags |= DO_DIRECT_IO;
	if (pOldObj->Characteristics & FILE_DEVICE_SECURE_OPEN)
		(*pFltObj)->Characteristics |= FILE_DEVICE_SECURE_OPEN;
	(*pFltObj)->Flags |= DO_POWER_PAGABLE;

	//将一个设备绑定到另一个设备上
	status = IoAttachDeviceToDeviceStackSafe(*pFltObj,//过滤设备
		pOldObj,//要被绑定的设备栈中的设备
		&topdev);//返回最终被绑定的设备
	if (status != STATUS_SUCCESS)
	{
		IoDeleteDevice(*pFltObj);
		*pFltObj = NULL;
		return status;
	}
	*pNext = topdev;

	//设置这个设备已经启动
	(*pFltObj)->Flags = (*pFltObj)->Flags & ~DO_DEVICE_INITIALIZING;

	return STATUS_SUCCESS;
}

// 这个函数在DriverEntry中调用，可以绑定所有的串口。
void ccpAttachAllComs(PDRIVER_OBJECT driver)
{
	ULONG i;
	PDEVICE_OBJECT com_ob;
	for (i = 0; i < CCP_MAX_COM_ID; i++)
	{
		// 获得object引用
		com_ob = ccpOpenCom(i);
		if (com_ob == NULL)
			continue;

		// 在这里绑定
		ccpAttachDevice(driver, com_ob, &s_fltobj[i], &s_nextobj[i]);
	}
}


#endif
