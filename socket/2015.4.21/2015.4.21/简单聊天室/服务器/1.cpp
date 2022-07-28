#include <iostream>
#define FD_SETSIZE 256
#include <Winsock2.h>
#include <vector>
#pragma comment(lib, "Ws2_32.lib")

#define _PORT 12345

void main()
{
	WSADATA wd;
	WSAStartup(MAKEWORD(1, 1), &wd);

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

	//业务循环
	while (1)
	{
		fd_set fs;
		FD_ZERO(&fs); //清空套接字集合
		FD_SET(sListen, &fs); //将监听套接字装入到套接字集合中
		for (int i = 0; i < client.size(); ++i) //将客户套接字装入到套接字集合中
			FD_SET(client[i], &fs);

		timeval t = {2, 500};
		select(0, &fs, 0, 0, &t);

		//循环当前发送网络事件的套接字
		for (int i = 0; i < fs.fd_count; ++i)
		{
			//若当前发生网络事件的套接字是
			//监听套接字，那么就是有人来连
			//接了
			if (fs.fd_array[i] == sListen)
			{
				sockaddr_in ci;
				int ci_len = sizeof(ci);
				SOCKET c = accept(sListen, (sockaddr*)&ci, &ci_len);
				std::cout<<inet_ntoa(ci.sin_addr)<<"连接到服务器，套接字为"<<c<<std::endl;
				client.push_back(c);
			}
			//若当前发生网络事件的套接字不是
			//监听套接字，那么就是有客户端发
			//送了数据了
			else
			{
				char buf[256];
				int r = recv(fs.fd_array[i], buf, 256, 0);
				if (r == 0 || r == SOCKET_ERROR)
				{
					std::cout<<fs.fd_array[i]<<"离开服务器！"<<std::endl;
					for (int j = 0; j < client.size(); ++j)
					{
						if (fs.fd_array[i] == client[j])
						{
							client.erase(client.begin() + j);
							break;
						}
					}
					closesocket(fs.fd_array[i]);
				}
				else
				{
					for (int j = 0; j < client.size(); ++j)
						send(client[j], buf, strlen(buf) + 1, 0);
				}
			}
		}
	}

	for (int i = 0; i < client.size(); ++i)
		closesocket(client[i]);
	closesocket(sListen);
	WSACleanup();

	system("pause");
}