#include <ntddk.h>

// 提供一个Unload函数只是为了
VOID DriverUnload(PDRIVER_OBJECT driver)
{
	UNREFERENCED_PARAMETER(driver);
	// 但是实际上我们什么都不做，只打印一句话:
	DbgPrint("DriverUnload: hello world");
}

// DriverEntry，入口函数。相当于main。
NTSTATUS DriverEntry(PDRIVER_OBJECT driver, PUNICODE_STRING reg_path)
{
	UNREFERENCED_PARAMETER(reg_path);

	DbgBreakPoint();
	DbgPrint("DriverEntry: hello world!\n");

	// 设置一个卸载函数便于这个函数能退出。
	driver->DriverUnload = DriverUnload;
	return STATUS_SUCCESS;
}
