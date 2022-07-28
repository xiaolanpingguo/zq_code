#include <iostream>
#include <WinSock2.h>
#include <vector>
#pragma comment(lib,"ws2_32.lib")
using namespace std;

#define SOCK_VERH 2
#define SOCK_VERL 2
#define _PORT 8888
//由于在默认情况下，recv函数和accept函数在数据未到来之前就会一直等待
//这样就阻塞了主线程，这样就会导致：
//1）.无法同一时间既接受请求又接受数据
//2）.无法同一时间等待多人发送数据
//那么解决上述2两个问题有两个办法：
//解决办法一：
//使用多线程，主线程用于accept其他客户端的连接，然后开启一个线程
//用于连接进来的客户端，这个开启的线程就专门用于为客户端服务
//但这样做有个弊端就是，如果有1000个客户端连接进来，那就开启了1000个线程，
//这样做的消耗就非常大
//解决办法二：使用多路复用函数
//int select(
//			int nfds//无用，仅仅是为了和Unix下面的select形参相同
//			fd_set *readfds//待检测可读性的套接字集合
//			fd_set *writefds//待检测可写性的套接字集合
//			fd_set *exceptfds//待检测发生异常的套接字集合
//			const struct timeval* timeout//等待时间，为0为无限等待)
//typedef struct fd_set//套接字集合结构体
//{
//		u_int fd_count;//数组中有效套接字的数量
//		SOCKET fd_array[FD_SETSIZE];//套接字数组，其中FD_SIZE
//									可以用条件编译来确定其数值大小
//}fd_set;
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

	//客户套接字
	std::vector<SOCKET> client;
	cout<<"服务器已经启动！"<<endl;
	while (1)
	{
		fd_set fs;
		//清空套接字集合
		FD_ZERO(&fs);
		//把监听套接字装入集合中
		FD_SET(sListen,&fs);
		//把客户端套接字装入到集合中
		for(int i = 0; i < client.size(); ++i)
			FD_SET(client.at(i),&fs);
		timeval t = {2.0};
		select(0,&fs,0,0,&t);
		//循环当前发生网络事件的套接字
		for(int i = 0; i < fs.fd_count; ++i)
		{
			//若当前网络事件的套接字是监听套接字
			//即说明有客户端连接进来了
			if(fs.fd_array[i] == sListen)
			{
				sockaddr_in ci;
				int ci_len = sizeof(ci);
				SOCKET c = accept(sListen,(sockaddr*)&ci,&ci_len);
				cout<<inet_ntoa(ci.sin_addr)<<"连接到服务器,套接字为："<<c<<endl;
				client.push_back(c);
			}
			//若当前不是监听套接字发生网络事件，
			//那就是客户端发出数据了
			else
			{
				char buf[256];
				int r = recv(fs.fd_array[i],buf,256,0);
				if( r == 0 || r == SOCKET_ERROR)
				{
					cout<<fs.fd_array[i]<<"离开了服务器"<<endl;
					for(int j = 0; j < client.size(); ++j)
					{
						if(fs.fd_array[i] == client.at(j))
						{
							client.erase(client.begin() + j);
							break;
						}
					}
				}
				else
					cout<<fs.fd_array[i]<<"说:"<<buf<<endl;
			}
		}
	}
	for(int i = 0; i < client.size(); ++i)
		closesocket(client[i]);
	closesocket(sListen);
	WSACleanup();
	system("pause");
}