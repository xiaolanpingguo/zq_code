#include <WinSock2.h>
#include <iostream>
#include <windows.h>
using namespace std;
#define PORT 8080
//显式连接套接字库
#pragma comment(lib,"WS2_32.lib")
void main()
{
	//定义WSADATA结构体对象
	WSADATA data;
	//定义版本号码
	WORD w=MAKEWORD(2,0);
	//发送给客户端的字符串
	char sztext[]="hell,i am client";
	char RecvBuf[1024]={};
	//初始化套接字库
	::WSAStartup(w,&data);
	//定义连接套接字和数据收发套接字句柄
	SOCKET s;
	//创建TCP套接字
	s=::socket(AF_INET,SOCK_STREAM,0);
	//定义套接字地址结构
	sockaddr_in addr;
	//初始化地址结构
	addr.sin_family=AF_INET;
	addr.sin_port=htons(PORT);
	addr.sin_addr.S_un.S_addr=inet_addr("127.0.0.1");
	//提示输出信息
	cout<<"服务器已经启动\r\n";
	//连接
	::connect(s,(sockaddr*)&addr,sizeof(addr));
	//?
	::send(s,sztext,sizeof(sztext),0);
	recv(s,RecvBuf,1024,0);
	printf("%s\r\n",RecvBuf);
	//关闭套接字句柄
	::closesocket(s);
	::WSACleanup();
	if(getchar())
		return;
	else
		Sleep(100);
}
