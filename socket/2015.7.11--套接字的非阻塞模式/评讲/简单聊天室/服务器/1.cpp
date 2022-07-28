#include <iostream>
#define FD_SETSIZE 256
#include <Winsock2.h>
#include <vector>
#pragma comment(lib, "Ws2_32.lib")

struct _CLIENT
{
	SOCKET s; //套接字
	unsigned long ip; //ip地址
};
std::vector<_CLIENT> clients; //客户表

void main()
{
	WSADATA wd;
	short version = MAKEWORD(1,1);
	WSAStartup(version, &wd);
	SOCKET s_listen = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	sockaddr_in si;
	si.sin_family = AF_INET;
	si.sin_port = htons(12345);
	si.sin_addr.S_un.S_addr = ADDR_ANY;
	bind(s_listen, (sockaddr*)&si, sizeof(si));
	listen(s_listen, 8);

	//业务循环
	while (1)
	{
		//定义套接字集合
		fd_set fs;

		//清空套接字集合
		FD_ZERO(&fs);

		//装载监听套接字
		FD_SET(s_listen, &fs);

		//装载数据套接字
		for (int i = 0; i < (int)clients.size(); ++i)
			FD_SET(clients[i].s, &fs);

		//多路复用
		timeval t = {5, 500};
		select(0, &fs, 0, 0, &t);

		//检测所有具备可读性的套接字
		for (int i = 0; i < (int)fs.fd_count; ++i)
		{
			//若当前具备可读性的套接字是监听套接字
			if (fs.fd_array[i] == s_listen)
			{
				sockaddr_in ci;
				int ci_len = sizeof(ci);
				SOCKET c = accept(s_listen, (sockaddr*)&ci, &ci_len);
				std::cout<<inet_ntoa(ci.sin_addr)<<"连接到服务器"<<std::endl;
				_CLIENT client = {c, ci.sin_addr.S_un.S_addr};
				clients.push_back(client);
			}
			//若当前具备可读性的套接字是数据套接字
			else
			{
				char buf[256];
				int r = recv(fs.fd_array[i], buf, 256, 0);
				if (r == 0 || r == SOCKET_ERROR)
				{
					//在表中查找发生错误的套接字
					int j;
					for (j = 0; j < clients.size(); ++j)
					{
						if (fs.fd_array[i] == clients[j].s)
							break;
					}
					in_addr ia;
					ia.S_un.S_addr = clients[j].ip;
					std::cout<<inet_ntoa(ia)<<"离开了服务器"<<std::endl;

					//关闭套接字
					closesocket(clients[j].s);

					//从客户表中删除套接字
					clients.erase(clients.begin() + j);
				}
				else
				{
					//给当前所有玩家群发消息
					for (int j = 0; j < clients.size(); ++j)
					{
						send(clients[j].s, buf, r, 0);
					}
				}
			}
		}

		std::cout<<"当前有"<<clients.size()<<"个玩家！"<<std::endl;
	}

	//关闭套接字
	closesocket(s_listen);

	//关闭网络环境
	WSACleanup();

	system("pause");
}