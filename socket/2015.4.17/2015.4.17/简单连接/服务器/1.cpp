//01)服务器
//{
//	01)bind：绑定套接字和地址信息
//	02)listen：设置套接字工作模式为监听模式
//	03)accept：接收来自客户端的连接请求
//}
//02)客户端
//{
//	01)connect：请求连接服务器
//	02)gethostbyname：根据域名得到IP地址
//	03)inet_addr：将字符串形式IP地址转换为整数形式IP地址
//	04)inet_ntoa：将整数形式IP地址转换为字符串形式IP地址
//	05)select：多路复用
//	06)FD_ZERO：清空套接字集合
//	07)FD_SET：设置指定套接字到指定套接字集合中
//	08)FD_ISSET：判断指定套接字是否在指定套接字集合中
//}
//03)共同
//{
//	01)WSAStartup：开启网络环境
//	02)WSACleanup：关闭网络环境
//	03)socket：创建套接字
//	04)shutdown：关闭套接字的发送或接收功能
//	05)closesocket：关闭套接字及其相关资源
//	06)recv：收数据
//	07)send：发数据
//	08)htons：short类型数据从本地字节顺序转网络字节顺序
//	09)ioctlsocket：套接字行为控制1
//	10)setsockopt：套接字行为控制2
//	11)WSAIoctl：套接字行为控制3
//	12)WSAGetLastError：得到当前网络错误
//}

#include <iostream>
#include <Winsock2.h>

#pragma comment(lib, "Ws2_32.lib")

#define _PORT 12345

void main()
{
	//1）开启网络环境
	//2）创建监听套接字
	//3）填充地址信息结构体
	//4）绑定监听套接字和地址信息结构体
	//5）设置监听套接字的工作方式为监听
	//6）等待客户端的连接请求
	//7）业务循环
	//8）关闭套接字
	//9）关闭网络环境

	//1）开启网络环境
	WSADATA wd;
	WSAStartup(
		MAKEWORD(1, 1), //MAKEWORD可以把两个数字合并到一个short的两个字节中
		&wd); //得到一些网络环境信息的结构体

	//2）创建监听套接字
	//   SOCKET是__w64 unsigned int的别名，套接字本质上是一个大的整数
	//   世界上有很多网络协议，不止TCP/IP一种，比如IPX、APPLETALK、WIFI
	//   等，这些协议中也分为使用流式传输或者使用报文传输两种工作方式
	SOCKET sListen = socket(
		AF_INET, //表示创建用于在internet上工作的套接字
		SOCK_STREAM, //表示创建工作方式为流式工作方式的套接字
		IPPROTO_TCP); //表示创建基于TCP协议的套接字

	//世界上所有的cpu从存储数据的高低字节不同可以分为两大类，一种
	//是大端存储，高位在前低位在后，一种是小端存储，低位在前高位在
	//后，比如：
	//int a = 1; //大端存储:00 00 00 01，小端存储：01 00 00 00
	//就是因为大端和小端在识别多字节数据的时候有不同的顺序，所以网
	//络数据传输中统一了一种存储方式，选择的是大端，并不是所有的数
	//都要进行这种统一的字节顺序处理，其实只有用于在网络上面进行路
	//由的数据，比如端口号等，只有这些数据需要统一一种存储，其它的
	//数据，比如我们的业务数据，如果能够明确服务器和客户端都是大端
	//或者都是小端，那么就无需进行统一处理
	//htons：short类型数据从本地字节顺序转网络字节顺序
	//htonl：long类型数据从本地字节顺序转网络字节顺序
	//ntohs：short类型数据从网络字节顺序转本地字节顺序
	//ntohl：long类型数据从网络字节顺序转本地字节顺序

	//3）填充地址信息结构体
	sockaddr_in si;
	si.sin_family = AF_INET; //表示本地址信息用于在internet上工作
	si.sin_port = htons(_PORT); //端口号
	si.sin_addr.S_un.S_addr = ADDR_ANY; //表示用于服务器的地址信息

	//4）绑定监听套接字和地址信息结构体
	bind(sListen, (sockaddr*)&si, sizeof(si));

	//5）设置监听套接字的工作方式为监听
	listen(
		sListen,
		8); //能够同时响应的连接请求的最大数量

	//6）等待客户端的连接请求
	//   本函数是阻塞函数，也就是说必须有对应的网络事件发生本函数
	//   才能返回，即必须有客户端进行连接本函数才返回否则一直等待
	//   ，本函数返回值是一个新的套接字，这个套接字就是和请求连接
	//   的客户端可以进行收发数据的套接字，我们对这个套接字调用send
	//   或者recv就可以向对应客户端发送、接收数据
	sockaddr_in ci;
	int ci_len = sizeof(ci);
	SOCKET sClient = accept(sListen, (sockaddr*)&ci, &ci_len);

	//得到客户端字符串形式的IP地址
	char* c_name = inet_ntoa(ci.sin_addr);
	std::cout<<c_name<<"连接到服务器"<<std::endl;

	//7）业务循环
	while (1)
	{
		char buf[256];

		//接收来自客户端的数据信息
		//本函数是阻塞函数，也就是说必须有对应的网络事件发生本函数
		//才能返回，即必须有客户端发送了数据本函数才返回否则一直等待
		recv(
			sClient, //对应客户端的数据套接字
			buf, //接收数据的内存地址
			256, //接收数据的内存长度
			0);

		std::cout<<c_name<<"说:"<<buf<<std::endl;
		if (strcmp(buf, "quit") == 0)
			break;
	}

	//8）关闭套接字
	closesocket(sClient);
	closesocket(sListen);

	//9）关闭网络环境
	WSACleanup();

	system("pause");
}