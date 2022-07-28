#include <iostream>
#include <WinSock2.h>
#include <vector>
#pragma comment(lib,"ws2_32.lib")
using namespace std;

#define SOCK_VERH 2
#define SOCK_VERL 2
#define _PORT 8888
//使用该模型的步骤如下:
//1).创建事件对象来接收网络事件
//WSAEVENT WSACreateEvent( void );
//该函数的返回值为一个事件对象句柄，它具有两种工作状态：
//已传信(signaled)和未传信(nonsignaled)以及两种工作模式：
//人工重设(manual reset)和自动重设(auto reset)。默认未未传信的工作状态和人工重设模式

//2).将事件对象与套接字关联，同时注册事件，使事件对象的工作状态从未传信转变未已传信。 
//int WSAEventSelect( SOCKET s,WSAEVENT hEventObject,long lNetworkEvents ); 
//s为套接字
//hEventObject为刚才创建的事件对象句柄

//3)I/O处理后，设置事件对象为未传信 
//BOOL WSAResetEvent( WSAEVENT hEvent );
//Hevent为事件对象
//成功返回TRUE，失败返回FALSE

//4).等待网络事件来触发事件句柄的工作状态：
//DWORD WSAWaitForMultipleEvents( DWORD cEvents,const WSAEVENT FAR * lphEvents, BOOL fWaitAll,DWORD dwTimeout, BOOL fAlertable )
////cEvent为为事件句柄的数目，其最大值为WSA_MAXIMUM_WAIT_EVENTS 
//lpEvent为事件句柄数组的指针
//fWaitAll指定等待类型：TRUE：当lphEvent数组重所有事件对象同时有信号时返回；
//FALSE：任一事件有信号就返回。
//dwTimeout为等待超时（毫秒）
//fAlertable为指定函数返回时是否执行完成例程
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
	//监听套接字
	SOCKET sListen = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	sockaddr_in si;
	si.sin_family = AF_INET;
	si.sin_port = htons(_PORT);
	si.sin_addr.S_un.S_addr = ADDR_ANY;

	bind(sListen, (sockaddr*)&si, sizeof(si));

	listen(sListen, 8);

	//套接字数组
	SOCKET SocketArray[WSA_MAXIMUM_WAIT_EVENTS];
	//事件对象数组
	WSAEVENT EventArray[WSA_MAXIMUM_WAIT_EVENTS];
	WSANETWORKEVENTS NetworkEvents;
	//总共的事件对象
	DWORD EventTotal = 0;
	DWORD Index ;
	//创建新的事件对象
	WSAEVENT NewEvent = WSACreateEvent();
	//把套接字数组和事件数组元素一一对应
	SocketArray[EventTotal] = sListen;
	EventArray[EventTotal++] = NewEvent;
	//关联事件和套接字
	WSAEventSelect(sListen,NewEvent,FD_ACCEPT | FD_CLOSE);
	cout<<"服务器已经启动！"<<endl;
	while (1)
	{
		//等待的所有套接字返回发生事件的套接字
		Index = WSAWaitForMultipleEvents(EventTotal,EventArray,FALSE,WSA_INFINITE,FALSE);
		if ( (Index == WSA_WAIT_FAILED) || (Index == WSA_WAIT_TIMEOUT) )
        {
            cout<<"WSAWaitForMultipleEvents调用失败!"<<endl;
            break;
        }
		//调查发生的是什么网络事件
		//调用了这个函数后，该套接字对应的事件对象也相应的从
		//已传信变为了未传信，也可以使用WSAResetEvent替代
		if(0 != WSAEnumNetworkEvents(SocketArray[Index-WSA_WAIT_EVENT_0],
			EventArray[Index-WSA_WAIT_EVENT_0],&NetworkEvents))
		{
			cout<<"WSAEnumNetworkEvents调用失败！"<<endl;
			break;
		}
		//网络事件为关闭连接
		if(NetworkEvents.lNetworkEvents & FD_CLOSE )
		{
			cout<<SocketArray[Index-WSA_WAIT_EVENT_0]<<"离开了服务器"<<endl;
			if(NetworkEvents.iErrorCode[FD_CLOSE_BIT] == 0)
			{
				//删除对应的套接字和事件
				closesocket(SocketArray[Index-WSA_WAIT_EVENT_0]);
				WSACloseEvent(EventArray[Index-WSA_WAIT_EVENT_0]);
				//数组前移
				for(DWORD i = Index-WSA_WAIT_EVENT_0; i < EventTotal; ++i)
				{
					SocketArray[i] = SocketArray[i+1];
					EventArray[i] = EventArray[i+1];
				}
				--EventTotal;
			}
		}
		//为连接事件
		if(NetworkEvents.lNetworkEvents & FD_ACCEPT )
		{
			if(NetworkEvents.iErrorCode[FD_ACCEPT_BIT] == 0)
			{
				//客户端地址
				sockaddr_in ci;
				int ci_len = sizeof(ci);
				//生成新的套接字用于收发数据
				SOCKET c = accept(sListen,(sockaddr*)&ci,&ci_len);
				cout<<inet_ntoa(ci.sin_addr)<<"连接到了服务器，套接字："<<c<<endl;
				//新套接字添加到数组中，并关联事件
				EventArray[EventTotal] = WSACreateEvent();
				WSAEventSelect(c,EventArray[EventTotal],FD_WRITE | FD_READ | FD_CLOSE);
				SocketArray[EventTotal++] = c;
			}
		}
		//读事件
		if(NetworkEvents.lNetworkEvents & FD_READ )
		{
			if(NetworkEvents.iErrorCode[FD_READ_BIT] == 0)
			{
				char buf[256];
				int r = recv(SocketArray[Index-WSA_WAIT_EVENT_0],buf,256,0);
				//未收到数据
				if(r == 0 || r == SOCKET_ERROR)
				{
					closesocket(SocketArray[Index-WSA_WAIT_EVENT_0]);
					WSACloseEvent(EventArray[Index-WSA_WAIT_EVENT_0]);
					for(DWORD i = Index-WSA_WAIT_EVENT_0; i < EventTotal; ++i)
					{
						SocketArray[i] = SocketArray[i+1];
						EventArray[i] = EventArray[i+1];
					}
					--EventTotal;
				}
				//收到数据
				else
					cout<<SocketArray[Index-WSA_WAIT_EVENT_0]<<"说"<<buf<<endl;
			}
		}
	}
	system("pause");
}