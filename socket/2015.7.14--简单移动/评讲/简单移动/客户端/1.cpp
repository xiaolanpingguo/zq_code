#include <iostream>
#define _WIN32_WINNT 0x0500 
#include <Winsock2.h>
#include <vector>
#include <ctime>
#include "NetWork.h"
#include "..\\game_protocol.h"
#pragma comment(lib, "Ws2_32.lib")

#define _WAIT_TIME 5
#define _MAP_W 16
#define _MAP_H 16
#define _VIEW_W 9
#define _VIEW_H 9
const char map[_MAP_W * _MAP_H]
=
{
	1,1,1,1,1,1,0,0,0,0,0,1,1,1,1,0,
	1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,
	1,1,0,1,1,1,1,1,1,0,1,1,1,0,1,1,
	1,1,0,1,1,1,1,1,1,0,1,1,1,1,1,1,
	1,1,0,1,1,1,1,1,0,1,1,1,1,0,1,1,
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

std::vector<_GAME_PLAYER> allplayer; //所有玩家（自己存在第0个位置）

void main()
{
	HWND hwnd = GetConsoleWindow();

	char server_ip[32];
	std::cout<<"请输入服务器ip地址：";
	std::cin>>server_ip;

	WSADATA wd;
	short version = MAKEWORD(1,1);
	WSAStartup(version, &wd);
	SOCKET s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	u_long no_blocking = TRUE;
	ioctlsocket(s, FIONBIO, &no_blocking);

	sockaddr_in si;
	si.sin_family = AF_INET;
	si.sin_port = htons(12345);
	si.sin_addr.S_un.S_addr = inet_addr(server_ip);
	
	//因为connect一定返回失败所以此处不检查
	connect(s, (sockaddr*)&si, sizeof(si));

	time_t t = time(0);
	while (1)
	{
		fd_set fs;
		FD_ZERO(&fs);
		FD_SET(s, &fs);
		timeval tv = {1, 0};
		select(0, 0, &fs, 0, &tv);
		if (fs.fd_count == 1)
			break;
		else
		{
			if (time(0) - t > _WAIT_TIME)
			{
				std::cout<<"无法连接服务器，";
				system("pause");
				closesocket(s);
				WSACleanup();
				return;
			}
		}
	}
	
	std::cout<<"连接服务器成功！"<<std::endl;

	CNetWork nw(s);

	//业务循环
	while (1)
	{
		//运作
		if (!nw.Run())
			break;

		//接收数据
		_RECV_DATA rd;
		while (nw.GetRecvDate(&rd))
		{
			_GAME_PROTOCOL* gp =  (_GAME_PROTOCOL*)rd.data;
			switch (gp->id)
			{
			case _NEW_PLAYER:
				{
					_SC_NEW_PLAYER* p0 = (_SC_NEW_PLAYER*)rd.data;

					//得到自己的信息
					allplayer.push_back(p0->new_player);

					//得到其它玩家信息
					for (int i = 0; i < p0->old_player_num; ++i)
						allplayer.push_back(p0->old_player[i]);

					break;
				}
			case _OLD_PLAYER:
				{
					_SC_OLD_PLAYER* p1 = (_SC_OLD_PLAYER*)rd.data;

					//加入新玩家信息
					allplayer.push_back(p1->new_player);

					break;
				}
			case _SOMEONE_MOVE:
				{
					_SC_SOMEONE_MOVE* p3 = (_SC_SOMEONE_MOVE*)rd.data;

					//移动指定玩家
					for (int i = 0; i < allplayer.size(); ++i)
					{
						if (p3->player.name == allplayer[i].name)
						{
							allplayer[i].x = p3->player.x;
							allplayer[i].y = p3->player.y;
							break;
						}
					}

					break;
				}
			case _PLAYER_QUIT:
				{
					_SC_PLAYER_QUIT* p3 = (_SC_PLAYER_QUIT*)rd.data;

					//删除指定玩家
					for (int i = 0; i < allplayer.size(); ++i)
					{
						if (p3->name == allplayer[i].name)
						{
							allplayer.erase(allplayer.begin() + i);
							break;
						}
					}

					break;
				}
			}
		}

		//输出
		system("cls");
		//1）生成新的地图
		char tmp_map[_MAP_W * _MAP_H];
		for (int i = 0; i < _MAP_W * _MAP_H; ++i)
			tmp_map[i] = map[i];
		//2）将所有玩家放入地图
		for (int i = 0; i < allplayer.size(); ++i)
		{
			int player_i = allplayer[i].x + allplayer[i].y * _MAP_W;
			tmp_map[player_i] = allplayer[i].name + 'a';
		}
		//3）根据本玩家为之决定视口，再根据视口进行绘制
		int vx, vy;
		if (allplayer[0].x < _VIEW_W / 2)
			vx = 0;
		else if (allplayer[0].x >= _MAP_W - _VIEW_W / 2)
			vx = _MAP_W - _VIEW_W;
		else
			vx = allplayer[0].x - _VIEW_W / 2;
		if (allplayer[0].y < _VIEW_H / 2)
			vy = 0;
		else if (allplayer[0].y >= _MAP_H - _VIEW_H / 2)
			vy = _MAP_H - _VIEW_H;
		else
			vy = allplayer[0].y - _VIEW_H / 2;
		for (int i = 0; i < _VIEW_W * _VIEW_H; ++i)
		{
			int rx = i % _VIEW_W;
			int ry = i / _VIEW_W;
			int map_i = (rx + vx) + (ry + vy) * _MAP_W;
			if (tmp_map[map_i] == 0)
				std::cout<<"■";
			else if (tmp_map[map_i] == 1)
				std::cout<<"□";
			else
			{
				const char* dy = "ＡＢＣＤＥＦＧＨＩＪＫＬＭＮＯＰＱＲＳＴＵＶＷＸＹＺ";
				char dy_name[3] = {};
				dy_name[0] = dy[(tmp_map[map_i] - 'a') * 2];
				dy_name[1] = dy[(tmp_map[map_i] - 'a') * 2 + 1];
				std::cout<<dy_name;
			}
			if (rx == _VIEW_W - 1)
				std::cout<<std::endl;
		}
		std::cout<<"["<<allplayer[0].x<<","<<allplayer[0].y<<"]"<<std::endl;

		//输入
		if (hwnd == GetForegroundWindow())
		{
			int x = allplayer[0].x;
			int y = allplayer[0].y;
			if (GetAsyncKeyState(VK_UP) & 1)
			{
				if (y > 0 && tmp_map[x + (y - 1) * _MAP_W] == 1)
					y -= 1;
			}
			if (GetAsyncKeyState(VK_DOWN) & 1)
			{
				if (y < _MAP_H - 1 && tmp_map[x + (y + 1) * _MAP_W] == 1)
					y += 1;
			}
			if (GetAsyncKeyState(VK_LEFT) & 1)
			{
				if (x > 0 && tmp_map[x - 1 + y * _MAP_W] == 1)
					x -= 1;
			}
			if (GetAsyncKeyState(VK_RIGHT) & 1)
			{
				if (x < _MAP_W - 1 && tmp_map[x + 1 + y * _MAP_W] == 1)
					x += 1;
			}
			//判断是否有移动
			if (x != allplayer[0].x || y != allplayer[0].y)
			{
				_CS_PLAYER_MOVE cs_pm;
				cs_pm.player.name = allplayer[0].name;
				cs_pm.player.x = x;
				cs_pm.player.y = y;
				nw.SendData(&cs_pm, sizeof(cs_pm));
			}
		}
		
		Sleep(20);
	}

	closesocket(s);
	WSACleanup();

	system("pause");
}