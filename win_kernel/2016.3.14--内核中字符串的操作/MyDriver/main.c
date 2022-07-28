#include <ntddk.h>

//1.字符串初始化
VOID StringInitTest()
{
	//字符串初始化(1)
	UNICODE_STRING str;
	str.Buffer = L"hello world0!";
	str.Length = str.MaximumLength = wcslen(L"hello world0") * sizeof(WCHAR);
	DbgPrint("%wZ", &str);

	//字符串初始化(2)
	RtlInitUnicodeString(&str, L"hello");
	DbgPrint("%wZ", &str);

	//初始化一个常数字符串常用到的宏
	UNICODE_STRING str1 = RTL_CONSTANT_STRING(L"hello world2!");
	DbgPrint("%wZ", &str1);
}

//2.字符串拷贝
VOID StringCopyTest()
{
	//字符串的拷贝
	UNICODE_STRING des;
	WCHAR buf[32];
	UNICODE_STRING src = RTL_CONSTANT_STRING(L"hello world3!");
	RtlInitEmptyUnicodeString(&des, buf, sizeof(buf));
	RtlCopyUnicodeString(&des, &src);
	DbgPrint("%wZ", &des);
}

//3.字符串连接
VOID StringCatTest()
{
	NTSTATUS status;
	WCHAR buf[32];
	UNICODE_STRING des;
	UNICODE_STRING src = RTL_CONSTANT_STRING(L"hello world4!");
	RtlInitEmptyUnicodeString(&des, buf, sizeof(buf));
	status = RtlAppendUnicodeStringToString(&des, &src);
	if (status == STATUS_BUFFER_TOO_SMALL)
	{
		DbgPrint(L"StringCatTest: STATUS_BUFFER_TOO_SMALL");
	}
	status = RtlAppendUnicodeToString(&des, L"987");
	if (status == STATUS_BUFFER_TOO_SMALL)
	{
		DbgPrint(L"StringCatTest: STATUS_BUFFER_TOO_SMALL");
	}
	DbgPrint("%wZ", &des);
}

//4.字符串比较
VOID StringCompareTest()
{
	UNICODE_STRING UnicodeString1;
	UNICODE_STRING UnicodeString2;
	RtlInitUnicodeString(&UnicodeString1, L"Hello World");
	RtlInitUnicodeString(&UnicodeString1, L"Hello");
	if (RtlEqualUnicodeString(&UnicodeString1, &UnicodeString2, TRUE))
		DbgPrint("UnicodeString1 and UnicodeString2 are equal\n");
	else
		DbgPrint("UnicodeString1 and UnicodeString2 are NOT equal\n");
}

//5.字符串变大写
VOID StringToUpperTest()
{
	//初始化UnicodeString1
	UNICODE_STRING UnicodeString1;
	UNICODE_STRING UnicodeString2;
	RtlInitUnicodeString(&UnicodeString1, L"Hello World");

	//变化前
	DbgPrint("UnicodeString1:%wZ\n", &UnicodeString1);

	//变大写
	RtlUpcaseUnicodeString(&UnicodeString2, &UnicodeString1, TRUE);

	//变化后
	DbgPrint("UnicodeString2:%wZ\n", &UnicodeString2);

	//销毁UnicodeString2（UnicodeString1不用销毁）
	RtlFreeUnicodeString(&UnicodeString2);
}

//6.字符串与整型相互转化
VOID StringToIntegerTest()
{
	//(1)字符串转换成数字
	{
		UNICODE_STRING UnicodeString1;
		ULONG lNumber;
		NTSTATUS nStatus;

		//初始化UnicodeString1
		RtlInitUnicodeString(&UnicodeString1, L"-100");
		nStatus = RtlUnicodeStringToInteger(&UnicodeString1, 10, &lNumber);
		if (NT_SUCCESS(nStatus))
		{
			DbgPrint("Conver to integer succussfully!\n");
			DbgPrint("Result:%d\n", lNumber);
		}
		else
		{
			DbgPrint("Conver to integer unsuccessfully!\n");
		}
	}
	//(2)数字转换成字符串
	{
		NTSTATUS nStatus;
		UNICODE_STRING UnicodeString2 = { 0 };
		//初始化UnicodeString2
		UnicodeString2.Buffer = (PWSTR)ExAllocatePool(PagedPool, 1024);
		UnicodeString2.MaximumLength = 1024;
		nStatus = RtlIntegerToUnicodeString(200, 10, &UnicodeString2);
		if (NT_SUCCESS(nStatus))
		{
			DbgPrint("Conver to string succussfully!\n");
			DbgPrint("Result:%wZ\n", &UnicodeString2);
		}
		else
		{
			DbgPrint("Conver to string unsuccessfully!\n");
		}

		//销毁UnicodeString2
		//注意!!UnicodeString1不用销毁
		RtlFreeUnicodeString(&UnicodeString2);
	}
}

//7. ANSI_STRING字符串与UNICODE_STRING字符串相互转换
VOID StringConverTest()
{
	//(1)将UNICODE_STRING字符串转换成ANSI_STRING字符串
	UNICODE_STRING UnicodeString1;
	ANSI_STRING AnsiString1;
	NTSTATUS nStatus;

	//初始化UnicodeString1
	RtlInitUnicodeString(&UnicodeString1, L"Hello World");
	nStatus = RtlUnicodeStringToAnsiString(&AnsiString1, &UnicodeString1, TRUE);
	if (NT_SUCCESS(nStatus))
	{
		DbgPrint("Conver succussfully!\n");
		DbgPrint("Result:%Z\n", &AnsiString1);
	}
	else
	{
		DbgPrint("Conver unsuccessfully!\n");
	}

	//销毁AnsiString1
	RtlFreeAnsiString(&AnsiString1);

	//(2)将ANSI_STRING字符串转换成UNICODE_STRING字符串
	{
		ANSI_STRING AnsiString2;
		UNICODE_STRING UnicodeString2;
		NTSTATUS nStatus;
		//初始化AnsiString2
		RtlInitString(&AnsiString2, "Hello World");
		nStatus = RtlAnsiStringToUnicodeString(&UnicodeString2, &AnsiString2, TRUE);
		if (NT_SUCCESS(nStatus))
		{
			DbgPrint("Conver succussfully!\n");
			DbgPrint("Result:%wZ\n", &UnicodeString2);
		}
		else
		{
			DbgPrint("Conver unsuccessfully!\n");
		}

		//销毁UnicodeString2
		RtlFreeUnicodeString(&UnicodeString2);
	}
}


//UNICODE_STRINGz转换为CHAR*
//输入UNICODE_STRING的指针，输出窄字符串，BUFFER需要已经分配好空间
VOID UnicodeToChar(PUNICODE_STRING dst, PCHAR src)
{
	ANSI_STRING string;
	RtlUnicodeStringToAnsiString(&string, dst, TRUE);
	strcpy(src, string.Buffer);
	RtlFreeAnsiString(&string);
}

//WCHAR*转换为CHAR*
//输入宽字符串首地址，输出窄字符串，BUFFER需要已经分配好空间
VOID WcharToChar(PWCHAR src, PCHAR dst)
{
	UNICODE_STRING uString;
	ANSI_STRING aString;
	RtlInitUnicodeString(&uString, src);
	RtlUnicodeStringToAnsiString(&aString, &uString, TRUE);
	strcpy(dst, aString.Buffer);
	RtlFreeAnsiString(&aString);
}
//CHAR*转WCHAR*
//输入窄字符串首地址，输出宽字符串，BUFFER需要已经分配好空间
VOID CharToWchar(PCHAR src, PWCHAR dst)
{
	UNICODE_STRING uString;
	ANSI_STRING aString;
	RtlInitAnsiString(&aString, src);
	RtlAnsiStringToUnicodeString(&uString, &aString, TRUE);
	wcscpy(dst, uString.Buffer);
	RtlFreeUnicodeString(&uString);
}

VOID DriverUnload(PDRIVER_OBJECT driver)
{
	DbgPrint("DriverUnload!\n");
}

NTSTATUS DriverEntry(PDRIVER_OBJECT driver, PUNICODE_STRING reg_path)
{
	DbgPrint("DriverEntry!\n");

	StringInitTest();
	StringCopyTest();
	StringCatTest();
	StringCompareTest();
	StringToUpperTest();
	StringToIntegerTest();
	StringConverTest();

	driver->DriverUnload = DriverUnload;
	
	return STATUS_SUCCESS;
}