#include <iostream>
#include <Winsock2.h>
using namespace std;
#pragma comment(lib, "Ws2_32.lib")

#define SOCK_VERH 2
#define SOCK_VERL 2
#define _PORT 8888
#define DATA_BUSIZE 5096

//自定义重叠结构
struct MyOverlapped
{
	WSAOVERLAPPED m_wsaol;			//重叠结构
	long		  m_lNetworkEvents; //事件类型（FD|READ / FD_WRITE)
	SOCKET        m_socket;			//socket句柄
	void*         m_pbuf;			//投递操作时的缓冲
	size_t		  m_szBufLen;		//缓冲长度
	DWORD	      m_dwTrasBytes;	//WSARecv和WSASend准备的参数
	DWORD		  m_dwFlags;		//WSARecv和WSASend准备的参数
};
//完成例程的投递函数
void CALLBACK CompletionRoutine(
								DWORD dwError,//标志咱们投递的重叠操作，比如WSARecv,完成的状态是什么
								DWORD cbTransfered,//指明了在重叠操作期间，实际传输的字节量是多大
								LPWSAOVERLAPPED lpOverlapped,//指明传递到最初的io调用内的一个重叠结构
								DWORD dwFlags);//返回操作结束时可能用的标志（一般没用）
void main()
{
	//版本与环境检查
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
        cout<<"无法初始化版本的Socket环境!"<<endl;
        WSACleanup( );
        return ; 
    }
	//初始化服务器套接字与地址
	SOCKET ListenSocket = socket(AF_INET, SOCK_STREAM ,IPPROTO_TCP);
	SOCKADDR_IN ServerAddr;
	ServerAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	ServerAddr.sin_family = AF_INET;
	ServerAddr.sin_port = htons(_PORT);
	//绑定套接字与地址
	bind(ListenSocket,(SOCKADDR*)&ServerAddr,sizeof(ServerAddr));
	//监听
	listen(ListenSocket,5);
	cout<<"正在等待客户端的接入。。"<<endl;
	//客户端套接字与地址
	SOCKADDR_IN ClientAddr;
	int len = sizeof(ClientAddr);
	SOCKET AcceptSocket = accept(ListenSocket,(SOCKADDR*)&ClientAddr,&len);
	cout<<inet_ntoa(ClientAddr.sin_addr)<<"已经连接进来了，套接字为："<<AcceptSocket<<endl;
	//准备的重叠结构与缓冲区
	WSABUF DataBuf = {};
	char buffer[DATA_BUSIZE] = {};
	DataBuf.buf = buffer;
	DataBuf.len = DATA_BUSIZE;
	WSAEVENT EventArray[WSA_MAXIMUM_WAIT_EVENTS]={};
	//将下列重要信息通过扩展OVERLAPPED的结构带到回调过程中去
	MyOverlapped AcceptOverlapped = {};
	AcceptOverlapped.m_socket = AcceptSocket;
	AcceptOverlapped.m_pbuf = DataBuf.buf;
	AcceptOverlapped.m_lNetworkEvents = FD_READ;
	AcceptOverlapped.m_szBufLen = DATA_BUSIZE;
	//填充WSARecv函数
	do{
		if(WSARecv(AcceptSocket,&DataBuf,1,&AcceptOverlapped.m_dwTrasBytes,&AcceptOverlapped.m_dwFlags,
				(WSAOVERLAPPED*)&AcceptOverlapped.m_wsaol,CompletionRoutine) == SOCKET_ERROR)
		{
			if(WSAGetLastError() != WSA_IO_PENDING)
			{
				system("pause");
				break;
			}
		}
		cout<<"重叠操作完成。。"<<endl;
	}while(WAIT_IO_COMPLETION == SleepEx(INFINITE,TRUE));
	if(INVALID_SOCKET != ListenSocket)
		closesocket(ListenSocket);
	WSACleanup();
}
//完成例程需要的函数
void CALLBACK CompletionRoutine(
								DWORD dwError,//标志咱们投递的重叠操作，比如WSARecv,完成的状态是什么
								DWORD cbTransfered,//指明了在重叠操作期间，实际传输的字节量是多大
								LPWSAOVERLAPPED lpOverlapped,//指明传递到最初的io调用内的一个重叠结构
								DWORD dwFlags)//返回操作结束时可能用的标志（一般没用）
{
	//得到正确的结构体指针
	MyOverlapped *pMy01 =CONTAINING_RECORD(lpOverlapped,MyOverlapped,m_wsaol);
	//断开了连接
	if(0 != dwError || 0 == cbTransfered)
	{
		cout<<pMy01->m_socket<<"退出了连接！"<<endl;
		closesocket(pMy01->m_socket);
		return ;
	}
	if(pMy01->m_lNetworkEvents == FD_READ)
	{
		cout<<pMy01->m_socket<<"说："<<(char*)pMy01->m_pbuf<<endl;
	}
}
