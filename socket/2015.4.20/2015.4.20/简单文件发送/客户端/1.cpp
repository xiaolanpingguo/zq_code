#include <iostream>
#include <Winsock2.h>

#pragma comment(lib, "Ws2_32.lib")

#define _PORT 12345

SOCKET sServer;

//用bool表示成功或失败
bool file_send()
{
	//得到文件名
	std::cout<<"请输入文件名：";
	char fn[256];
	std::cin>>fn;

	//打开文件
	FILE* pf = 0;
	fopen_s(&pf, fn, "rb");
	if (!pf)
	{
		std::cout<<"无法打开指定文件！";
		return true;
	}

	//得到文件大小和内容
	fseek(pf, 0, SEEK_END);
	int fs = ftell(pf);
	rewind(pf);
	char* fd = new char[strlen(fn) + 1 + fs];
	fread(fd + strlen(fn) + 1, 1, fs, pf);
	//strcpy_s(fd, strlen(fn) + 1 + fs, fn);
	memcpy(fd, fn, strlen(fn) + 1);
	fclose(pf);

	//得到当前要发送的总字节数
	int all_bytes = strlen(fn) + 1 + fs;

	//发送总字节数到服务器
	if (SOCKET_ERROR == send(sServer, (char*)&all_bytes, 4, 0))
		return false;

	//发送数据
	int cur_bytes = 0; //当前已经发送的字节数
	while (cur_bytes < all_bytes)
	{
		int r = send(sServer, fd + cur_bytes, all_bytes - cur_bytes, 0);
		if (r == SOCKET_ERROR)
			return false;
		else
			cur_bytes += r;
	}
	return true;
}

void main()
{
	WSADATA wd;
	WSAStartup(MAKEWORD(1, 1), &wd);

	sServer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	char server_ip[256];
	std::cout<<"请输入服务器的IP地址：";
	std::cin>>server_ip;
	sockaddr_in si;
	si.sin_family = AF_INET;
	si.sin_port = htons(_PORT);
	si.sin_addr.S_un.S_addr = inet_addr(server_ip); //服务器IP地址

	if (SOCKET_ERROR == connect(sServer, (sockaddr*)&si, sizeof(si)))
	{
		std::cout<<"无法连接服务器，";
		system("pause");
		closesocket(sServer);
		WSACleanup();
		return;
	};

	while (1)
	{
		system("cls");
		std::cout<<"1)发送\n2)退出\n请选择：";
		int sel;
		std::cin>>sel;
		if (sel == 1)
		{
			bool b = file_send();
			if (!b)
				break;
		}
		else if (sel == 2)
			break;

	}

	closesocket(sServer);
	WSACleanup();

	system("pause");
}