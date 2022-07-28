#include<iostream>
#include<time.h>
#include<windows.h>

#define _WORLD_MAP_W 200
#define _WORLD_MAP_H 200
#define _WORLD_MAP_S (_WORLD_MAP_W * _WORLD_MAP_H)

#define _VIEW_PORT_W 21
#define _VIEW_PORT_H 21
#define _VIEW_PORT_S (_VIEW_PORT_W * _VIEW_PORT_H)

#define _KD 0
#define _ZA 1
#define _ZA_NUM 1000

#define M_UP 0
#define M_DOWN 1
#define M_LEFT 2
#define M_RIGHT 3

void main()
{
	srand(time(0));

	char map[_WORLD_MAP_S] = {};

	for(int i = 0; i < _ZA_NUM; ++i)
	{
		int x = rand()% _WORLD_MAP_W;
		int y = rand()% _WORLD_MAP_H;
		map[x + y * _WORLD_MAP_W] = _ZA;
	}

	int x = 0;
	int y = 0;
	int dir = -1;
	while(1)
	{
		int vx,vy;//视口左上角在大地图上的坐标
		//卷屏的处理
		if(x < _VIEW_PORT_W / 2)
			vx = 0;
		else if(x >= _WORLD_MAP_W - _VIEW_PORT_W / 2)
			vx = _WORLD_MAP_W - _VIEW_PORT_W;
		else
			vx = x -  _VIEW_PORT_W / 2;
		

		if(y < _VIEW_PORT_H / 2)
			vy = 0;
		else if(y >= _WORLD_MAP_H - _VIEW_PORT_H / 2)
			vy = _WORLD_MAP_H - _VIEW_PORT_H;
		else
			vy = y -  _VIEW_PORT_H / 2;

		system("cls");

		for(int i = 0; i < _VIEW_PORT_S; ++i)
		{
			int cx = i % _VIEW_PORT_W;
			int cy = i / _VIEW_PORT_W;
			if((cx + vx) == x &&  (cy + vy) == y)
				std::cout<<"★";
			else
			{
				if(map[(cx + vx) + (cy + vy)* _WORLD_MAP_W] == _KD)
					std::cout<<"□";
				else
					std::cout<<"■";
			}
			if(i % _VIEW_PORT_W == _VIEW_PORT_W - 1)
				std::cout<<std::endl;
		}

		if(GetAsyncKeyState(VK_UP) & 0x8000)
			dir = M_UP;

		if(GetAsyncKeyState(VK_DOWN) & 0x8000)
			dir = M_DOWN;	

		if(GetAsyncKeyState(VK_LEFT) & 0x8000)
			dir = M_LEFT;

		if(GetAsyncKeyState(VK_RIGHT) & 0x8000)
			dir = M_RIGHT;

		if(dir == M_UP && y > 0 && map[x + ( y - 1) * _WORLD_MAP_W ] == _KD)
			--y;
		else if(dir == M_DOWN && y < _WORLD_MAP_H - 1 && map[x + ( y + 1) * _WORLD_MAP_W ] == _KD)
			++y;
		else if(dir == M_LEFT && x > 0 && map[(x - 1) + y * _WORLD_MAP_W ] == _KD)
			--x;
		else if(dir == M_RIGHT && x < _WORLD_MAP_W - 1 && map[(x + 1) + y * _WORLD_MAP_W ] == _KD)
			++x;

		Sleep(40);

	}
	system("pause");
}