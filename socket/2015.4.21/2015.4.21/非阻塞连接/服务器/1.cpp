#include <iostream>
#define _WIN32_WINNT 0x0500
#include <Winsock2.h>
#include <windows.h>
#pragma comment(lib, "Ws2_32.lib")

void main()
{
	//得到控制台窗口句柄
	HWND hwnd = GetConsoleWindow();

	WSADATA wd;
	WSAStartup(MAKEWORD(1, 1), &wd);
	SOCKET sListen = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	//设置套接字为非阻塞工作方式，如果设置监听套接字为
	//非阻塞的，那么这个监听套接字得到的数据套接字都会
	//被自动设置为非阻塞套接字
	unsigned long nonblocking = 1;
	ioctlsocket(sListen, FIONBIO, &nonblocking);

	sockaddr_in si;
	si.sin_family = AF_INET;
	si.sin_port = htons(12345);
	si.sin_addr.S_un.S_addr = ADDR_ANY;
	bind(sListen, (sockaddr*)&si, sizeof(si));
	listen(sListen, 8);
	sockaddr_in ci;
	int ci_len = sizeof(ci);

	SOCKET sClient;
	while (1)
	{
		sClient = accept(sListen, (sockaddr*)&ci, &ci_len);
		if (INVALID_SOCKET == sClient)
		{
			if (WSAGetLastError() == WSAEWOULDBLOCK)
				std::cout<<"当前无人连接"<<std::endl;
			else
			{
				std::cout<<"真的出错了，";
				system("pause");
				closesocket(sListen);
				WSACleanup();
				return;
			}
		}
		else
			break;
	}

	system("cls");

	while (1)
	{
		//GetForegroundWindow可以得到当前操作系统中位于
		//最顶层的窗口，可以用来判断本控制台是不是在最
		//顶层
		if (GetForegroundWindow() == hwnd)
		{
			for (char i = 'A'; i <= 'Z'; ++i)
			{
				if (GetAsyncKeyState(i) & 0x8000)
					send(sClient, &i, 1, 0);
			}
		}

		char buf[256];
		int r = recv(sClient, buf, 256, 0);
		if (r > 0)
		{
			for (int i = 0; i < r; ++i)
				std::cout<<buf[i];
		}
		else if (r == SOCKET_ERROR)
		{
			if (WSAGetLastError() == WSAEWOULDBLOCK)
				;
			else
			{
				std::cout<<"真的出错了，";
				system("pause");
				closesocket(sClient);
				closesocket(sListen);
				WSACleanup();
				return;
			}
		}
		else if (r == 0)
			break;

		Sleep(20);
	}

	closesocket(sClient);
	closesocket(sListen);
	WSACleanup();

	system("pause");
}