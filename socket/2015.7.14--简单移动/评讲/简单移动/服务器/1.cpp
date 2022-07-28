#include <iostream>
#include <ctime>
#include <Winsock2.h>
#include <vector>
#include "NetWork.h"
#include "..\\game_protocol.h"
#pragma comment(lib, "Ws2_32.lib")

#define _MAX_PLAYER 26

#define _MAP_W 16
#define _MAP_H 16

const char map[_MAP_W * _MAP_H]
=
{
	1,1,1,1,1,1,0,0,0,0,0,1,1,1,1,0,
	1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,
	1,1,0,1,1,1,1,1,1,0,1,1,1,0,1,1,
	1,1,0,1,1,1,1,1,1,0,1,1,1,1,1,1,
	1,1,0,1,1,1,1,1,1,1,1,1,1,0,1,1,
	1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,0,1,0,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,
	1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,1,
	1,1,1,1,0,1,1,1,1,0,1,1,1,1,1,1,
	1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,0,1,1,1,1,0,1,1,0
};

struct _CLIENT
{
	SOCKET s; //套接字
	CNetWork nw; //数据收发
	_GAME_PLAYER gp; //玩家信息
};
std::vector<_CLIENT> clients; //客户表

void main()
{
	srand((unsigned int)time(0));
	WSADATA wd;
	short version = MAKEWORD(1,1);
	WSAStartup(version, &wd);
	SOCKET s_listen = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	u_long no_blocking = TRUE;
	ioctlsocket(s_listen, FIONBIO, &no_blocking);
	sockaddr_in si;
	si.sin_family = AF_INET;
	si.sin_port = htons(12345);
	si.sin_addr.S_un.S_addr = ADDR_ANY;
	bind(s_listen, (sockaddr*)&si, sizeof(si));
	listen(s_listen, 8);

	//初始化空地下标
	int kd[_MAP_W * _MAP_H], kd_num = 0;
	for (int i = 0; i < _MAP_W * _MAP_H; ++i)
	{
		if (map[i] == 1)
			kd[kd_num++] = i;
	}

	//业务循环
	while (1)
	{
		//1）接收连接请求
		if (clients.size() < _MAX_PLAYER)
		{
			sockaddr_in ci;
			int ci_len = sizeof(ci);
			SOCKET s = accept(s_listen, (sockaddr*)&ci, &ci_len);
			if (s == INVALID_SOCKET)
			{
				if (WSAGetLastError() != WSAEWOULDBLOCK)
				{
					std::cout<<"程序发生真正的错误，";
					system("pause");
					break;
				}
			}
			else
			{
				_CLIENT c;

				//得到套接字
				c.s = s;

				//初始化收发
				c.nw.SetSocket(c.s);
				
				//初始化新玩家
				bool b[_MAX_PLAYER] = {};
				for (int i = 0; i < (int)clients.size(); ++i)
					b[clients[i].gp.name] = true;
				for (c.gp.name = 0; c.gp.name < _MAX_PLAYER; ++c.gp.name)
				{
					if (!b[c.gp.name])
						break;
				}
				int xb = kd[rand() % kd_num];
				c.gp.x = xb % _MAP_W;
				c.gp.y = xb / _MAP_W;

				//设置0号协议并发送
				_SC_NEW_PLAYER sc_np;
				sc_np.new_player = c.gp;
				sc_np.old_player_num = clients.size();
				for (int i = 0; i < sc_np.old_player_num; ++i)
					sc_np.old_player[i] = clients[i].gp;
				c.nw.SendData(&sc_np, 20 + sc_np.old_player_num * 12);
				
				//设置1号协议并发送
				_SC_OLD_PLAYER sc_op;
				sc_op.new_player = c.gp;
				for (int i = 0; i < (int)clients.size(); ++i)
					clients[i].nw.SendData(&sc_op, sizeof(sc_op));

				//新玩家入表
				clients.push_back(c);
			}
		}

		//2）收到来自玩家的数据
		for (int i = 0; i < (int)clients.size(); ++i)
		{
			_RECV_DATA rd;
			while (clients[i].nw.GetRecvDate(&rd))
			{
				//因为服务器只能收到2号协议，所以无需判断
				//协议的类别，但是在客户端就必须判断了
				_CS_PLAYER_MOVE* cs_pm = (_CS_PLAYER_MOVE*)rd.data;
				
				//更新玩家表
				for (int j = 0; j < clients.size(); ++j)
				{
					if (clients[j].gp.name == cs_pm->player.name)
					{
						clients[j].gp.x = cs_pm->player.x;
						clients[j].gp.y = cs_pm->player.y;
						break;
					}
				}

				//设置3号消息并群发
				_SC_SOMEONE_MOVE sc_sm;
				sc_sm.player = cs_pm->player;
				for (int j = 0; j < clients.size(); ++j)
					clients[j].nw.SendData(&sc_sm, sizeof(sc_sm));

				clients[i].nw.ReleaseRecvData(&rd);
			}
		}

		//所有玩家的收发运作，可能要进行删除操作，所以用迭代器进行遍历
		for (std::vector<_CLIENT>::iterator it = clients.begin(); it != clients.end(); )
		{
			if (it->nw.Run())
				++it;
			else
			{
				//设置4号消息并群发
				_SC_PLAYER_QUIT sc_pq;
				sc_pq.name = it->gp.name;
				for (int j = 0; j < clients.size(); ++j)
				{
					if (clients[j].gp.name != it->gp.name)
						clients[j].nw.SendData(&sc_pq, sizeof(sc_pq));
				}

				//当前玩家断开
				it->nw.End(); //释放所有可能未释放的内存
				closesocket(it->s); //关闭套接字
				it = clients.erase(it);
			}
		}
	}

	for (int i = 0; i < clients.size(); ++i)
	{
		closesocket(clients[i].s);
		clients[i].nw.End();
	}
	closesocket(s_listen);
	WSACleanup();

	system("pause");
}