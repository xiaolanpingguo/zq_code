#include <iostream>
#include <Winsock2.h>
using namespace std;
#pragma comment(lib, "Ws2_32.lib")

#define SOCK_VERH 2
#define SOCK_VERL 2
#define _PORT 8888
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
	WORD wVer = MAKEWORD(SOCK_VERH,SOCK_VERL);
    WSADATA wd;
	int err = ::WSAStartup(wVer,&wd);
	if(0 != err)
    {
       cout << "无法初始化"<<SOCK_VERH<<"."<<SOCK_VERL<<"版本的Socket环境!" << endl;
        return ;
    }
    if ( LOBYTE( wd.wVersion ) != SOCK_VERH ||
        HIBYTE( wd.wVersion ) != SOCK_VERL ) 
    {
       cout<<"无法初始化%d.%d版本的Socket环境!"<<endl;
        WSACleanup( );
        return ; 
    }

	//2）创建套接字
	SOCKET sServer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	//3）根据服务器IP地址填充地址信息结构体
	sockaddr_in si;
	si.sin_family = AF_INET;
	si.sin_port = htons(_PORT);
	si.sin_addr.S_un.S_addr = inet_addr("127.0.0.1"); //服务器IP地址

	//4）通过套接字和地址信息结构体请求连接服务器
	if (SOCKET_ERROR == connect(sServer, (sockaddr*)&si, sizeof(si)))
	{
		std::cout<<"无法连接服务器，";
		system("pause");
		closesocket(sServer);
		WSACleanup();
		return;
	};

	//5）业务循环
	while (1)
	{
		char buf[256];
		std::cout<<"请输入要发送的字符串：";
		std::cin>>buf;

		//发送数据到服务器
		send(
			sServer, //对应服务器的数据套接字
			buf, //发送数据的内存地址
			strlen(buf) + 1, //发送数据的内存长度
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