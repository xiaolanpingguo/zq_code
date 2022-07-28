#include<iostream>
#include<time.h>
#include<windows.h>

#define _MAP_W 10
#define _MAP_H 10
#define _MAP_S (_MAP_W * _MAP_H)

#define _XY(x,y) ((x) + (y) * _MAP_W)
#define _XY_X(i) ((i) % _MAP_W)
#define _XY_Y(i) ((i) / _MAP_W)

#define _MOVE_UP    0
#define _MOVE_DOWN  1
#define _MOVE_LEFT  2
#define _MOVE_RIGHT 3

void main()
{
	//先取得随机种子
	srand(time(0));
	//● ◆ ■
	//
	int x1;//记录●位置
	int y1;
	int x2;//记录◆位置
	int y2;
	int x3;//记录■位置
	int y3;

	int dir1;//记录●方向
	int dir2;//记录◆方向
	
	//初始●状态
	x1 = 0;
	y1 = 0;
	dir1 = _MOVE_DOWN;

	//初始◆状态
	x2 = _MAP_W - 1;
	y2 = _MAP_H - 1;
	dir2 = _MOVE_UP;

	//初始■状态
	int suijixiabiao = rand()%(_MAP_S - 2) + 1;
	x3 = _XY_X(suijixiabiao);
	y3 = _XY_Y(suijixiabiao);
	//初始■状态1
	//x3 = rand()%_MAP_W;
	//y3 = rand()%_MAP_H;
	//if(y3 == 0)
	//	x3 += 1;
	//else if(y3 == _MAP_H - 1)
	//	x3 -= 1;
	
	while(1)
	{
		//绘制地图
		system("cls");
		for(int i = 0; i < _MAP_S; ++i)
		{
			if(x1 == x2 && y1 == y2 && i == _XY(x1,y1))
				std::cout<<"★";
			else if(i == _XY(x1,y1))
				std::cout<<"●";
			else if(i == _XY(x2,y2))
				std::cout<<"◆";
			else if(i == _XY(x3,y3))
				std::cout<<"■";
			else 
				std::cout<<"□";

			if(_XY_X(i) == _MAP_W - 1)
				std::cout<<std::endl;
		}
		//位移的处理
		//●
		switch(dir1)
		{
		case _MOVE_UP:
			{
				if(y1 > 0 && (x1 != x3 || (y1 - 1) != y3))
					y1--;
			}
			break;
		case _MOVE_DOWN:
			{
				if(y1 < _MAP_H - 1 && (x1 != x3 || (y1 + 1) != y3))
					y1++;
			}
			break;
		case _MOVE_LEFT:
			{
				if(x1 > 0 && (y1 != y3 || (x1 - 1) != x3))
					x1--;
			}
			break;
		case _MOVE_RIGHT:
			{
				if(x1 < _MAP_W - 1 && (y1 != y3 || (x1 + 1) != x3))
					x1++;
			}
			break;
		}
		//◆
		switch(dir2)
		{
		case _MOVE_UP:
			{
				if(y2 > 0 && (x2 != x3 || (y2 - 1) != y3))
					y2--;
			}
			break;
		case _MOVE_DOWN:
			{
				if(y2 < _MAP_H - 1 && (x2 != x3 || (y2 + 1) != y3))
					y2++;
			}
			break;
		case _MOVE_LEFT:
			{
				if(x2 > 0 && (y2 != y3 || (x2 - 1) != x3))
					x2--;
			}
			break;
		case _MOVE_RIGHT:
			{
				if(x2 < _MAP_W - 1 && (y2 != y3 || (x2 + 1) != x3))
					x2++;
			}
			break;
		}

		//获取按键
		//●
		if(GetAsyncKeyState('W') & 1)
			dir1 = _MOVE_UP;
		if(GetAsyncKeyState('S') & 1)
			dir1 = _MOVE_DOWN;
		if(GetAsyncKeyState('A') & 1)
			dir1 = _MOVE_LEFT;
		if(GetAsyncKeyState('D') & 1)
			dir1 = _MOVE_RIGHT;
		//◆
		if(GetAsyncKeyState(VK_UP) & 1)
			dir2 = _MOVE_UP;
		if(GetAsyncKeyState(VK_DOWN) & 1)
			dir2 = _MOVE_DOWN;
		if(GetAsyncKeyState(VK_LEFT) & 1)
			dir2 = _MOVE_LEFT;
		if(GetAsyncKeyState(VK_RIGHT) & 1)
			dir2 = _MOVE_RIGHT;

		Sleep(40);
	}

	system("pause");
}