#ifndef FILE_OPERATION_H
#define FILE_OPERATION_H

#include <Ntifs.h>


#define RN_MAX_PATH 2048
#define SFLT_POOL_TAG 'fuck'
#define MAX_PATH2 4096
#define kmalloc(_s)	ExAllocatePoolWithTag(NonPagedPool, _s, 'SYSQ')
#define kfree(_p)	ExFreePool(_p)


//复制文件
BOOLEAN ZwCopyFile(IN PWSTR ustrDestFile, IN PWSTR ustrSrcFile)
{
	HANDLE hSrcFile = NULL;
	HANDLE hDestFile = NULL;
	PVOID buffer = NULL;
	ULONG length = 0;
	LARGE_INTEGER offset = { 0 };
	IO_STATUS_BLOCK Io_Status_Block = { 0 };
	OBJECT_ATTRIBUTES obj_attrib;
	NTSTATUS status;
	BOOLEAN bRet = FALSE;
	UNICODE_STRING unSrcFile;
	UNICODE_STRING unDestFile;
	WCHAR SrcBuf[256] = { 0 };
	WCHAR DestBuf[256] = { 0 };
	wcscpy(SrcBuf, L"\\??\\");
	wcscat(SrcBuf, ustrSrcFile);
	wcscpy(DestBuf, L"\\??\\");
	wcscat(DestBuf, ustrDestFile);
	RtlInitUnicodeString(&unSrcFile, SrcBuf);
	RtlInitUnicodeString(&unDestFile, DestBuf);
	do
	{
		//在内核中，无论是打开文件，注册表还是设备，都会先调用
		//这个函数初始化一个OBJECT_ATTRIBUTES的结构体
		InitializeObjectAttributes(&obj_attrib,
			&unSrcFile,
			OBJ_CASE_INSENSITIVE |//名字不区分大小写
			OBJ_KERNEL_HANDLE,//内核句柄，不用顾忌权限问题
			NULL,
			NULL);

		//打开一个文件
			status = ZwCreateFile(&hSrcFile,//句柄指针
				GENERIC_READ,//读权限
				&obj_attrib,//上面初始化的结构体，里面包含了文件路径
				&Io_Status_Block,//表示操作的结果
				NULL,//定义文件初始化分配大小，仅关系到创建文件或重写文件
				FILE_ATTRIBUTE_NORMAL,//新建立的文件属性，一般为0或者FILE_ATTRIBUTE_NORMAL
				FILE_SHARE_READ,//共享访问权限
				FILE_OPEN,//代表打开文件
				FILE_NON_DIRECTORY_FILE |
				FILE_SYNCHRONOUS_IO_NONALERT,//表示同步打开一个文件，而非目录
				NULL,
				0);
		if (!NT_SUCCESS(status))
		{
			bRet = FALSE;
			break;
		}

		// 打开目标文件
		InitializeObjectAttributes(&obj_attrib,
			&unDestFile,
			OBJ_CASE_INSENSITIVE |
			OBJ_KERNEL_HANDLE,
			NULL,
			NULL);
		status = ZwCreateFile(&hDestFile,
			GENERIC_WRITE,
			&obj_attrib,
			&Io_Status_Block,
			NULL,
			FILE_ATTRIBUTE_NORMAL,
			FILE_SHARE_READ,
			FILE_OPEN_IF,
			FILE_NON_DIRECTORY_FILE |
			FILE_SYNCHRONOUS_IO_NONALERT,
			NULL,
			0);
		if (!NT_SUCCESS(status))
		{
			bRet = FALSE;
			break;
		}

		//为buffer分配4KB空间
		buffer = ExAllocatePool(NonPagedPool, 1024 * 4);
		if (buffer == NULL)
		{
			bRet = FALSE;
			break;
		}

		// 复制文件
		while (1)
		{
			length = 4 * 1024;
			// 读取源文件
			status = ZwReadFile(hSrcFile,//文件句柄
				NULL,//一个事件，用于异步读取
				NULL,//回调例程，用于异步
				NULL,//填NULL即可
				&Io_Status_Block,//返回状态结果，同创建时的同名参数
				buffer,//文件内容读到这个缓冲区
				length,//缓冲区长度
				&offset,//文件偏移量
				NULL);//附加信息，填NULL即可
			if (!NT_SUCCESS(status))
			{
				// 如果状态为 STATUS_END_OF_FILE，说明文件已经读取到末尾
				if (status == STATUS_END_OF_FILE)
				{
					bRet = TRUE;
					break;
				}
			}

			// 获得实际读取的长度
			length = (ULONG)Io_Status_Block.Information;

			// 写入到目标文件
			status = ZwWriteFile(hDestFile,
				NULL,
				NULL,
				NULL,
				&Io_Status_Block,
				buffer,
				length,
				&offset,
				NULL);
			if (!NT_SUCCESS(status))
			{
				bRet = FALSE;
				break;
			}

			// 移动文件指针
			offset.QuadPart += length;
		}
	} while (0);

	if (hSrcFile)
	{
		ZwClose(hSrcFile);
	}
	if (hDestFile)
	{
		ZwClose(hDestFile);
	}
	if (buffer != NULL)
	{
		ExFreePool(buffer);
	}

	return bRet;
}

//删除文件或文件夹
NTSTATUS ZwDeleteFileFolder(IN PWSTR wsFileName)
{
	NTSTATUS st;
	OBJECT_ATTRIBUTES ObjectAttributes;
	UNICODE_STRING UniFileName;
	WCHAR Buf[256] = { 0 };
	wcscpy(Buf, L"\\??\\");
	wcscat(Buf, wsFileName);

	//把 WCHAR*转化为 UNICODE_STRING
	RtlInitUnicodeString(&UniFileName, Buf);

	//设置OBJECT对象并使用ZwDeleteFile删除
	InitializeObjectAttributes(&ObjectAttributes,
		&UniFileName,
		OBJ_CASE_INSENSITIVE | OBJ_KERNEL_HANDLE,
		NULL,
		NULL);

	return ZwDeleteFile(&ObjectAttributes); 
}

//重命名文件或文件夹
NTSTATUS ZwRenameFile(IN PWSTR DstFileName, IN PWSTR SrcFileName)
{
	UNICODE_STRING ObjectName;
	WCHAR SrcBuf[256] = { 0 };
	WCHAR DestBuf[256] = { 0 };
	wcscpy(SrcBuf, L"\\??\\");
	wcscat(SrcBuf, SrcFileName);
	wcscpy(DestBuf, L"\\??\\");
	wcscat(DestBuf, DstFileName);
	HANDLE FileHandle = NULL;
	OBJECT_ATTRIBUTES ObjectAttributes;
	IO_STATUS_BLOCK IoStatus;
	NTSTATUS Status;
	PFILE_RENAME_INFORMATION RenameInfo = NULL;

	//设置重命名的信息
	RenameInfo = (PFILE_RENAME_INFORMATION)ExAllocatePoolWithTag(NonPagedPool,
		sizeof(FILE_RENAME_INFORMATION) + RN_MAX_PATH * sizeof(WCHAR), SFLT_POOL_TAG);
	if (RenameInfo == NULL)
	{
		return STATUS_INSUFFICIENT_RESOURCES;
	}

	//分配内存
	RtlZeroMemory(RenameInfo, sizeof(FILE_RENAME_INFORMATION) + RN_MAX_PATH *
		sizeof(WCHAR));
	RenameInfo->FileNameLength = wcslen(DestBuf) * sizeof(WCHAR);
	wcscpy(RenameInfo->FileName, DestBuf);
	RenameInfo->ReplaceIfExists = 0;
	RenameInfo->RootDirectory = NULL;

	//设置源文件信息并获得句柄
	RtlInitUnicodeString(&ObjectName, SrcBuf);
	InitializeObjectAttributes(&ObjectAttributes,
		&ObjectName,
		OBJ_CASE_INSENSITIVE,
		NULL,
		NULL);

	//文件重命名
	Status = ZwCreateFile(&FileHandle,
		SYNCHRONIZE | DELETE,
		&ObjectAttributes,
		&IoStatus,
		NULL,
		0,
		FILE_SHARE_READ,
		FILE_OPEN,
		FILE_SYNCHRONOUS_IO_NONALERT |
		FILE_NO_INTERMEDIATE_BUFFERING,
		NULL,
		0);
	if (!NT_SUCCESS(Status))
	{
		ExFreePoolWithTag(RenameInfo, SFLT_POOL_TAG);
		return Status;
	}

	//设置文件信息
	Status = ZwSetInformationFile(FileHandle,
		&IoStatus,
		RenameInfo,
		sizeof(FILE_RENAME_INFORMATION) +
		RN_MAX_PATH * sizeof(WCHAR),
		FileRenameInformation);
	if (!NT_SUCCESS(Status))
	{
		ExFreePoolWithTag(RenameInfo, SFLT_POOL_TAG);
		ZwClose(FileHandle);
		return Status;
	}

	ExFreePoolWithTag(RenameInfo, SFLT_POOL_TAG);
	ZwClose(FileHandle);

	return Status;
}

//获取文件大小
ULONG64 GetFileSize(PWSTR wsFileName)
{
	IO_STATUS_BLOCK iostatus = { 0 };
	NTSTATUS ntStatus = 0;
	FILE_STANDARD_INFORMATION fsi = { 0 };
	IO_STATUS_BLOCK Io_Status_Block = { 0 };
	HANDLE hFile = NULL;
	OBJECT_ATTRIBUTES obj_attrib;
	UNICODE_STRING UniFileName;
	WCHAR Buf[256] = { 0 };
	wcscpy(Buf, L"\\??\\");
	wcscat(Buf, wsFileName);
	RtlInitUnicodeString(&UniFileName, Buf);
	InitializeObjectAttributes(&obj_attrib,
		&UniFileName,
		OBJ_CASE_INSENSITIVE |//名字不区分大小写
		OBJ_KERNEL_HANDLE,//内核句柄，不用顾忌权限问题
		NULL,
		NULL);

	//打开一个文件
	ntStatus = ZwCreateFile(&hFile,//句柄指针
		GENERIC_READ,//读权限
		&obj_attrib,//上面初始化的结构体，里面包含了文件路径
		&Io_Status_Block,//表示操作的结果
		NULL,//定义文件初始化分配大小，仅关系到创建文件或重写文件
		FILE_ATTRIBUTE_NORMAL,//新建立的文件属性，一般为0或者FILE_ATTRIBUTE_NORMAL
		FILE_SHARE_READ,//共享访问权限
		FILE_OPEN,//代表打开文件
		FILE_NON_DIRECTORY_FILE |
		FILE_SYNCHRONOUS_IO_NONALERT,//表示同步打开一个文件，而非目录
		NULL,
		0);
	if (!NT_SUCCESS(ntStatus))
	{
		if (hFile)
			ZwClose(hFile);
		return 0;
	}

	ntStatus = ZwQueryInformationFile(hFile,
		&iostatus,
		&fsi,
		sizeof(FILE_STANDARD_INFORMATION),
		FileStandardInformation);
	if (!NT_SUCCESS(ntStatus))
	{
		ZwClose(hFile);
		return 0;
	}

	if (hFile)
	{
		ZwClose(hFile);
	}

	return fsi.EndOfFile.QuadPart;
}

//枚举文件
HANDLE MyFindFirstFile(LPSTR lpDirectory, PFILE_BOTH_DIR_INFORMATION pDir, ULONG uLength)
{
	char strFolder[MAX_PATH2] = { 0 };
	STRING astrFolder;
	UNICODE_STRING ustrFolder;
	OBJECT_ATTRIBUTES oa;
	IO_STATUS_BLOCK ioStatus;
	NTSTATUS ntStatus;
	HANDLE hFind = NULL;
	memset(strFolder, 0, MAX_PATH2);
	strcpy(strFolder, "\\??\\");
	strcat(strFolder, lpDirectory);
	RtlInitString(&astrFolder, strFolder);
	if (RtlAnsiStringToUnicodeString(&ustrFolder, &astrFolder, TRUE) == 0)
	{
		InitializeObjectAttributes(&oa, &ustrFolder, OBJ_CASE_INSENSITIVE, NULL, NULL);
		ntStatus = IoCreateFile(
			&hFind,
			FILE_LIST_DIRECTORY | SYNCHRONIZE | FILE_ANY_ACCESS,
			&oa,
			&ioStatus,
			NULL,
			FILE_ATTRIBUTE_NORMAL,
			FILE_SHARE_READ | FILE_SHARE_WRITE,
			FILE_OPEN,	//FILE_OPEN
			FILE_DIRECTORY_FILE | FILE_SYNCHRONOUS_IO_NONALERT | FILE_OPEN_FOR_BACKUP_INTENT,
			NULL,
			0,
			CreateFileTypeNone,
			NULL,
			IO_NO_PARAMETER_CHECKING);
		RtlFreeUnicodeString(&ustrFolder);
		if (ntStatus == 0 && hFind)
		{
			ntStatus = ZwQueryDirectoryFile(
				hFind, // File Handle
				NULL, // Event
				NULL, // Apc routine
				NULL, // Apc context
				&ioStatus, // IoStatusBlock
				pDir, // FileInformation
				uLength, // Length
				FileBothDirectoryInformation, // FileInformationClass
				TRUE, // ReturnSingleEntry
				NULL, // FileName
				FALSE //RestartScan
				);
			if (ntStatus != 0)
			{
				ZwClose(hFind);
				hFind = NULL;
			}
		}
	}

	return hFind;
}

BOOLEAN MyFindNextFile(HANDLE hFind, PFILE_BOTH_DIR_INFORMATION pDir, ULONG uLength)
{
	IO_STATUS_BLOCK ioStatus;
	NTSTATUS ntStatus;
	ntStatus = ZwQueryDirectoryFile(
		hFind, // File Handle
		NULL, // Event
		NULL, // Apc routine
		NULL, // Apc context
		&ioStatus, // IoStatusBlock
		pDir, // FileInformation
		uLength, // Length
		FileBothDirectoryInformation, // FileInformationClass
		FALSE, // ReturnSingleEntry
		NULL, // FileName
		FALSE //RestartScan
		);
	if (ntStatus == 0)
		return TRUE;
	else
		return FALSE;
}

ULONG SearchDirectory(LPSTR lpPath)
{
	ULONG muFileCount = 0;
	HANDLE hFind = NULL;
	PFILE_BOTH_DIR_INFORMATION pDir;
	char* strBuffer = NULL;
	char strFileName[255 * 2];
	ULONG uLength = MAX_PATH2 * 2 + sizeof(FILE_BOTH_DIR_INFORMATION);
	strBuffer = (PCHAR)kmalloc(uLength);
	pDir = (PFILE_BOTH_DIR_INFORMATION)strBuffer;
	hFind = MyFindFirstFile(lpPath, pDir, uLength);
	if (hFind)
	{
		kfree(strBuffer);
		uLength = (MAX_PATH2 * 2 + sizeof(FILE_BOTH_DIR_INFORMATION)) * 0x2000;
		strBuffer = (PCHAR)kmalloc(uLength);
		pDir = (PFILE_BOTH_DIR_INFORMATION)strBuffer;
		if (MyFindNextFile(hFind, pDir, uLength))
		{
			while (TRUE)
			{
				memset(strFileName, 0, 255 * 2);
				memcpy(strFileName, pDir->FileName, pDir->FileNameLength);
				if (strcmp(strFileName, "..") != 0 && strcmp(strFileName, ".") != 0)
				{
					if (pDir->FileAttributes & FILE_ATTRIBUTE_DIRECTORY)
					{
						DbgPrint("[目录]%S\n", strFileName);
					}
					else
					{
						DbgPrint("[文件]%S\n", strFileName);
					}
					muFileCount++;
				}
				if (pDir->NextEntryOffset == 0) 
					break;
				pDir = (PFILE_BOTH_DIR_INFORMATION)((char *)pDir + pDir->NextEntryOffset);
			}
			kfree(strBuffer);
		}
		ZwClose(hFind);
	}

	return muFileCount;
}

#endif
