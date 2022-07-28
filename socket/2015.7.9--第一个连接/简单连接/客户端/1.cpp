#include <iostream>
#include <Winsock2.h>
#pragma comment(lib, "Ws2_32.lib")

void main()
{
	WSADATA wd;
	WSAStartup(0x0101, &wd);

	//创建用于和服务器进行数据收发的数据套接字
	SOCKET s_server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	char server_ip[256];
	std::cout<<"请输入服务器ip地址：";
	std::cin>>server_ip;

	//填充一个地址信息结构体
	sockaddr_in si;
	si.sin_family = AF_INET;
	si.sin_port = htons(12345);
	si.sin_addr.S_un.S_addr = inet_addr(server_ip);

	//请求连接服务器
	if (SOCKET_ERROR == connect(s_server, (sockaddr*)&si, sizeof(si)))
	{
		std::cout<<"无法连接服务器，";
		system("pause");
		closesocket(s_server);
		WSACleanup();
		return;
	}

	std::cout<<"成功连接服务器！"<<std::endl;

	//业务循环
	while (1)
	{
		char buf[256];
		std::cout<<"请输入要发送给服务器的字符串：";
		std::cin>>buf;

		//发送数据
		send(
			s_server, //数据套接字
			buf, //待发送数据的内存首地址
			strlen(buf) + 1, //待发送数据的长度
			0); //标志，填0即可

		if (strcmp(buf, "exit") == 0)
			break;
	}

	//关闭套接字
	closesocket(s_server);

	//关闭网络环境
	WSACleanup();

	system("pause");
}

//本机ip地址：127.0.0.1