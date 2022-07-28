#include <iostream>
#include <Winsock2.h>
#include <string>
#include <process.h>

#pragma comment(lib, "Ws2_32.lib")

#define _PORT 12345

SOCKET sServer;

unsigned int __stdcall recv_server(void*)
{
	while (1)
	{
		char buf[256];
		recv(sServer, buf, 256, 0);
		std::cout<<buf<<std::endl;
	}
}

void main()
{
	//1）开启网络环境
	//2）创建套接字
	//3）根据服务器IP地址填充地址信息结构体
	//4）通过套接字和地址信息结构体请求连接服务器
	//5）业务循环
	//6）关闭套接字
	//7）关闭网络环境

	 //1）开启网络环境
	WSADATA wd;
	WSAStartup(MAKEWORD(1, 1), &wd);

	//2）创建套接字
	sServer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	//3）根据服务器IP地址填充地址信息结构体
	char server_ip[256];
	std::cout<<"请输入服务器的IP地址：";
	std::cin>>server_ip;
	sockaddr_in si;
	si.sin_family = AF_INET;
	si.sin_port = htons(_PORT);
	si.sin_addr.S_un.S_addr = inet_addr(server_ip); //服务器IP地址

	//4）通过套接字和地址信息结构体请求连接服务器
	if (SOCKET_ERROR == connect(sServer, (sockaddr*)&si, sizeof(si)))
	{
		std::cout<<"无法连接服务器，";
		system("pause");
		closesocket(sServer);
		WSACleanup();
		return;
	};

	char nickname[256];
	std::cout<<"请输入昵称：";
	std::cin>>nickname;

	//专门开启一个线程来接收来自服务器的数据
	_beginthreadex(0, 0, recv_server, 0, 0, 0);

	//5）业务循环
	while (1)
	{
		char buf[256];
		std::cout<<"请输入要发送的字符串：";
		std::cin>>buf;

		std::string s = nickname;
		s += "说：";
		s += buf;

		//发送数据到服务器
		send(
			sServer, //对应服务器的数据套接字
			s.c_str(), //发送数据的内存地址
			s.length() + 1, //发送数据的内存长度
			0);

		//如果发送的是quit就退出程序
		if (strcmp(buf, "quit") == 0)
			break;
	}

	//6）关闭套接字
	closesocket(sServer);

	//7）关闭网络环境
	WSACleanup();

	system("pause");
}