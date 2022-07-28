//01)服务器
//{
//	01)bind：绑定套接字和地址信息
//	02)listen：设置套接字为监听模式
//	03)accept：接收来自客户端的连接
//}
//02)客户端
//{
//	01)connect：连接指定ip地址、port端口的服务器
//	02)gethostbyname：根据域名得到ip地址
//	03)inet_addr：字符串形式的ip地址转整数形式的ip地址
//	04)inet_ntoa：整数形式的ip地址转字符串形式的ip地址
//	05)select：多路复用
//	06)FD_ZERO：清空套接字集合
//	07)FD_SET：设置套接字到套接字集合
//	08)FD_ISSET：判断套接字是否在套接字集合
//}
//03)共同
//{
//	01)WSAStartup：开启网络环境
//	02)WSACleanup：结束网络环境
//	03)socket：创建套接字
//	04)shutdown：停止套接字的收功能或发功能
//	05)closesocket：关闭套接字及其相关所有资源
//	06)recv：收数据（返回值告知了我们收到多少字节数据）
//	07)send：发数据（返回值告知了我们发送多少字节数据）
//	08)htons：本地双字节整数转网络双字节整数
//	09)ioctlsocket：设置套接字选项1
//	10)setsockopt：设置套接字选项2
//	11)WSAIoctl：设置套接字选项3
//	12)WSAGetLastError：得到最后发生的网络错误信息
//}

#include <iostream>
#include <Winsock2.h>
#pragma comment(lib, "Ws2_32.lib")

void main()
{
	WSADATA wd;

	//开启网络环境（网络环境版本号，用于获得一些信息的结构体对象）
	//网络环境版本号是一个short变量，主版本号在高字节、副版本号在
	//低字节，一般来说我们使用1.1版或2.2版，在1.1版本中我们能够使
	//用的套接字相关函数都是伯克利套接字函数（伯克利套接字是加州大
	//学伯克利分校的计算机实验室最早在unix上面实现一套套接字函数，
	//这套函数的通用范围是最广的，unix和linux下面都是它们作为网络
	//函数），在2.2版本中我们可以使用更多的Windows提供的基于Windows
	//的更高层次的网络函数（WSA开头），但是这些函数不利于移植，版本
	//号可以用宏MAKEWORD(主版本号，副版本号)来填写
	short version = MAKEWORD(1,1);
	WSAStartup(version, &wd);

	//在服务器端有两种不同用处套接字
	//1）监听套接字：监听有无客户端来进行连接的套接字
	//2）数据套接字：和客户端的套接字形成了套接字对的
	//               服务器的套接字，可以和客户端收发
	//               数据
	SOCKET s_listen = socket(
		AF_INET, //AF_INET表示作用于internet上的套接字
		SOCK_STREAM, //SOCK_STREAM表示创建流式套接字
		IPPROTO_TCP); //IPPROTO_TCP表示创建TCP套接字

	//填充一个地址信息结构体
	sockaddr_in si;
	si.sin_family = AF_INET; //表面该地址作用于internet
	si.sin_port = htons(12345); //端口号
	si.sin_addr.S_un.S_addr = ADDR_ANY; //表示运行来自任何地址的连接

	//绑定套接字和地址信息结构体，使得套接字中带上了地址信息
	bind(s_listen, (sockaddr*)&si, sizeof(si));

	//设置指定套接字为监听套接字，后面的整数表示能够同时
	//响应的连接请求的最大数量，此次填写8是一个经验数字，
	//表示如果同时有n（>8）个客户端来进行连接请求，那么最
	//多能够响应8个人的请求，即accept函数能够正常返回8次
	listen(s_listen, 8);

	//接收来自客户端的连接（阻塞函数），填写监听套接字以及
	//用于获得客户端信息的地址信息结构体，一旦有客户端连接
	//进来，那么本函数的返回值就是和客户度相连的那个数据套
	//接字，地址信息结构体也可以得到客户端的信息
	sockaddr_in si_c;
	int len = sizeof(si_c);
	SOCKET s_client = accept(s_listen, (sockaddr*)&si_c, &len);
	std::cout<<inet_ntoa(si_c.sin_addr)<<"连接到服务器"<<std::endl;

	//业务循环
	while (1)
	{
		char buf[256];

		//接收来自数据套接字的网络数据（阻塞函数）
		recv(
			s_client, //数据套接字
			buf, //存放网络数据的内存首地址
			256, //存放网络数据的内存长度
			0); //标志，填0即可

		Beep(500, 100);

		//打印来自客户端的字符串
		std::cout<<inet_ntoa(si_c.sin_addr)<<"说："<<buf<<std::endl;

		if (strcmp(buf, "exit") == 0)
			break;
	}

	//关闭套接字
	closesocket(s_client);
	closesocket(s_listen);

	//关闭网络环境
	WSACleanup();

	system("pause");
}