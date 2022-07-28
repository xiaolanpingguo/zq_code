#include <iostream>
#include <Winsock2.h>
using namespace std;
#pragma comment(lib, "Ws2_32.lib")

#define SOCK_VERH 2
#define SOCK_VERL 2
#define _PORT 8888
#define DATA_BUSIZE 5096

void main()
{
	WORD wVer = MAKEWORD(SOCK_VERH,SOCK_VERL);
    WSADATA wd;
    int err = ::WSAStartup(wVer,&wd);
    if(0 != err)
    {
       cout<<"无法初始化Socket2系统环境!"<<endl;
        return ;
    }
    if ( LOBYTE( wd.wVersion ) != SOCK_VERH ||
        HIBYTE( wd.wVersion ) != SOCK_VERL ) 
    {
       cout << "无法初始化"<<SOCK_VERH<<"."<<SOCK_VERL<<"版本的Socket环境!" << endl;
        WSACleanup( );
        return ; 
    }
	//缓冲区结构
	WSABUF DataBuf;
	char buffer[DATA_BUSIZE] = {};
	DataBuf.buf = buffer;
	DataBuf.len = DATA_BUSIZE;
	//重叠结构
	WSAOVERLAPPED AcceptOverlapped;
	//置零
	ZeroMemory(&AcceptOverlapped,sizeof(AcceptOverlapped));
	//事件数组
	WSAEVENT EventArray[WSA_MAXIMUM_WAIT_EVENTS] = {};
	//事件总数
	DWORD EventTotal = 0;
	//关联事件
	EventArray[EventTotal] = WSACreateEvent();
	AcceptOverlapped.hEvent = EventArray[EventTotal];
	EventTotal ++;
	//收到的字符串长度
	DWORD RecvBytes = 0;
	DWORD BytesTransferred = 0;
	//WSARecv中的参数
	DWORD Flags = 0;
	SOCKET sListen = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	//填充服务器地址结构体
	sockaddr_in si;
	si.sin_family = AF_INET;
	si.sin_port = htons(_PORT);
	si.sin_addr.S_un.S_addr = ADDR_ANY;
	bind(sListen,(sockaddr*)&si,sizeof(si));
	listen(sListen,5);
	cout<<"服务器已经启动。。"<<endl;
	//客户端地址信息
	sockaddr_in ci;
	int ci_len = sizeof(ci);
	SOCKET AcceptSocket = accept(sListen,(sockaddr*)&ci,&ci_len);
	cout<<inet_ntoa(ci.sin_addr)<<"连接到服务器,套接字为："<<AcceptSocket<<endl;
	while (1)
	{
		//接收数据
		if(WSARecv(AcceptSocket,&DataBuf,1,&RecvBytes,&Flags,&AcceptOverlapped,NULL)
			== SOCKET_ERROR)
		{
			//返回WSA_IO_PENDING 是正常情况，不是的话就出问题了
			//只能关闭套接字了
			if(WSAGetLastError() != WSA_IO_PENDING)
			{
				closesocket(AcceptSocket);
				WSACloseEvent(EventArray[EventTotal]);
			}
		}
		//事件触发
		DWORD Index = WSAWaitForMultipleEvents(EventTotal,EventArray,FALSE,WSA_INFINITE,FALSE);
		//重置事件信号
		WSAResetEvent(EventArray[Index - WSA_WAIT_EVENT_0]);
		//获得重叠结构的结果
		WSAGetOverlappedResult(AcceptSocket,&AcceptOverlapped,&BytesTransferred,FALSE,&Flags);
		//收到的数据为0，代表客户端已经退出了服务器
		if(BytesTransferred == 0)
		{
			cout<<AcceptSocket<<"退出了服务器!"<<endl;
			closesocket(AcceptSocket);
			WSACloseEvent(EventArray[EventTotal]);
			break;
		}
		//发送数据
		if(WSASend(AcceptSocket,&DataBuf,1,&RecvBytes,Flags,&AcceptOverlapped,NULL)
			== SOCKET_ERROR)
			cout<<"发送出错！"<<endl;
		cout<<AcceptSocket<<"说:"<<DataBuf.buf<<endl;
	}
	closesocket(sListen);
	WSACleanup();
	system("pause");
}