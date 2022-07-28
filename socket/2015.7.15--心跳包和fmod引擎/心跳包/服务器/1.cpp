#include <iostream>
#include <Winsock2.h>
#include <MSTcpIP.h>
#pragma comment(lib, "Ws2_32.lib")

void main()
{
	WSADATA wd;
	short version = MAKEWORD(1,1);
	WSAStartup(version, &wd);
	SOCKET s_listen = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	u_long no_blocking = TRUE;
	ioctlsocket(s_listen, FIONBIO, &no_blocking);
	sockaddr_in si;
	si.sin_family = AF_INET;
	si.sin_port = htons(12345);
	si.sin_addr.S_un.S_addr = ADDR_ANY;
	bind(s_listen, (sockaddr*)&si, sizeof(si));
	listen(s_listen, 8);

	SOCKET s;

	//接收连接
	while (1)
	{
		sockaddr_in ci;
		int ci_len = sizeof(ci);
		s = accept(s_listen, (sockaddr*)&ci, &ci_len);
		if (s == INVALID_SOCKET)
		{
			if (WSAGetLastError() != WSAEWOULDBLOCK)
			{
				std::cout<<"程序发生真正的错误，";
				system("pause");
				break;
			}
		}
		else
			break;
	}

	std::cout<<"有客户端连接成功！"<<std::endl;

	//心跳包是用于检测一个TCP连接是否还存活的一种
	//机制，它内部还是使用发包和收包的方式进行检测
	//，可以帮助我们来检查无法通过普通手段发现的连
	//接断开情况（比如断网线），一旦设置了心跳包，
	//那么TCP内部会每隔一段固定时间就发一个数据包
	//到对方，对方收到数据包之后也会回发一个数据包
	//回来，如果连接是存活的那么肯定可以收到对方回
	//发的包，如果连接失效了那么就收不到对方回发的
	//包了，一段时间之内还没有收到的话，TCP将判定这
	//个连接已经失效了，那么会设置recv返回SOCKET_ERROR
	//并且错误是WSAENETRESET

	//开启心跳包
	BOOL b = TRUE;
	setsockopt(
		s,
		SOL_SOCKET,
		SO_KEEPALIVE,
		(const char*)&b,
		sizeof(b));

	//设置心跳包的时间
	DWORD dw;
	tcp_keepalive tka
		=
	{
		1, //1开0关
		10 * 1000, //如果在10秒内都没有收到对方发送过来的数据，那么开始进入发送心跳包的状态
		5 * 1000 //从发送状态时间开始，每隔5秒发送一次心跳包进行检测
	};
	WSAIoctl(
		s,
		SIO_KEEPALIVE_VALS,
		&tka,
		sizeof(tka),
		0,
		0,
		&dw,
		0,
		0);

	//TCP的11种状态变迁图，最后一种状态WAIT_2_TIMES

	while (1)
	{
		char buf[256];
		int r = recv(s, buf, 256, 0);
		if (r == 0)
		{
			std::cout<<"优雅断开！"<<std::endl;
			break;
		}
		else if (r == SOCKET_ERROR)
		{
			if (WSAEWOULDBLOCK != WSAGetLastError())
			{
				std::cout<<"发生错误！"<<std::endl;
				break;
			}
		}
		else
			std::cout<<"收到数据"<<std::endl;

		Sleep(20);
	}

	closesocket(s);
	closesocket(s_listen);
	WSACleanup();

	system("pause");
}