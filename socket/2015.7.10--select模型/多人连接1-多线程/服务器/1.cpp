#include <iostream>
#include <Winsock2.h>
#include <process.h>
#pragma comment(lib, "Ws2_32.lib")

SOCKET client[256]; //客户数组
int client_num = 0; //客户数量

unsigned int _stdcall recv_client(void* p)
{
	//业务循环
	while (1)
	{
		char buf[256];
		recv(*((SOCKET*)p), buf, 256, 0);
		std::cout<<*((SOCKET*)p)<<"说"<<buf<<std::endl;
	}

	return 1u;
}

void main()
{
	WSADATA wd;
	short version = MAKEWORD(1,1);
	WSAStartup(version, &wd);
	SOCKET s_listen = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	sockaddr_in si;
	si.sin_family = AF_INET;
	si.sin_port = htons(12345);
	si.sin_addr.S_un.S_addr = ADDR_ANY;
	bind(s_listen, (sockaddr*)&si, sizeof(si));
	listen(s_listen, 8);

	//主线程接收连接
	while (1)
	{
		sockaddr_in si_c;
		int len = sizeof(si_c);
		client[client_num] = accept(s_listen, (sockaddr*)&si_c, &len);
		std::cout<<inet_ntoa(si_c.sin_addr)<<"连接到服务器"<<std::endl;
		//第4个参数是要求填写一个地址，这个地
		//址会被用来初始化线程函数的形式参数
		_beginthreadex(0, 0, recv_client, &client[client_num], 0, 0);
		client_num += 1;
	}

	//关闭套接字
	closesocket(s_listen);

	//关闭网络环境
	WSACleanup();

	system("pause");
}