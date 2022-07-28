#include <WinSock2.h>
#include <iostream>
#include <windows.h>
#define _PORT_ 8500
using namespace std;
//显式连接套接字库
#pragma comment(lib,"WS2_32.lib")
void main()
{
	//定义WSADATA结构体对象
	WSADATA data;
	//定义版本号码
	WORD w=MAKEWORD(2,0);
	//发送给客户端的字符串
	char sztext[256]={};
	//初始化套接字库
	::WSAStartup(w,&data);
	//定义连接套接字和数据收发套接字句柄
	SOCKET s,s1;
	//创建TCP套接字
	s=::socket(AF_INET,SOCK_STREAM,0);
	//定义套接字地址结构
	sockaddr_in addr,addr2;
	//获取套接字地址结构大小
	int n=sizeof(addr2);
	//初始化地址结构
	addr.sin_family=AF_INET;
	addr.sin_port=htons( _PORT_);
	addr.sin_addr.S_un.S_addr=INADDR_ANY;
	//绑定套接字
	::bind(s,(sockaddr*)&addr,sizeof(addr));
	//监听套接字
	::listen(s,5);
	//提示输出信息
	cout<<"服务器已经启动\r\n";
	cout<<"正在等待客户端连接"<<endl;
	while(1)
	{
		//接受连接请求
		s1=::accept(s,(sockaddr*)&addr2,&n);
		if(s1!=NULL)
		{
			printf("%s已经连接上\r\n",inet_ntoa(addr2.sin_addr));
			while(1)
			{
				char rec[256]={};
				recv(s1,rec,256,0);
				cout<<"客户端说："<<rec<<endl;
				//向客户端发送欢迎信息
				cout<<"请输入要发送的内容:"<<endl<<"服务器说：";
				cin>>sztext;
				::send(s1,sztext,sizeof(sztext),0);
			}
		}
		//关闭套接字句柄
		::closesocket(s);
		::closesocket(s1);
		//释放套接字库
		::WSACleanup();
		if(getchar())
		{
			return;
		}
		else
		{
			Sleep(100);
		}
	}
}