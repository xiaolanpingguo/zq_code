#include <iostream>
#include <conio.h>

#define _MAP_W_ 10
#define _MAP_H_ 10
#define _MAP_S_ _MAP_W_*_MAP_H_

#define _XY(x,y) (x) + (y) * _MAP_W_
#define _XY_X(i) (i) % _MAP_W_
#define _XY_Y(i) (i) / _MAP_H_

#define _TL 0
#define _ZA 1
#define _XZ 2
#define _MU 3
#define _YX 4
#define _KUN 5
#define _QIU 6

#define _GAME_INIT 0
#define _GAME_RUN  1

#define _IN_MAP(x,y) ((x) >= 0 && (x) < _MAP_W_ && (y) >= 0 && (y) < _MAP_H_)

void main()
{
	//游戏准备工作
	int GameState = _GAME_INIT;
	const char allmap[]
	= 
	{
		1,1,1,1,1,1,1,1,1,1,
		1,0,0,0,0,0,0,0,0,1,
		1,0,4,0,0,0,0,0,0,1,
		1,0,3,3,1,1,1,0,0,1,
		1,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,1,
		1,0,0,2,0,2,0,5,0,1,
		1,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,1,
		1,1,1,1,1,1,1,1,1,1,//第一关

		1,1,1,1,1,1,1,1,1,1,
		1,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,1,0,0,0,1,
		1,0,3,3,1,1,1,0,0,1,
		1,0,0,4,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,1,
		1,0,5,2,0,2,0,5,0,1,
		1,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,1,
		1,1,1,1,1,1,1,1,1,1//第二关
	};
	int curstage = 0;//当前关卡
	
	char map[_MAP_S_];//当前的关卡地图
	int x;
	int y;//英雄坐标
	int MUNum;
	//正式进入游戏循环
	while(1)
	{
		if(GameState == _GAME_INIT)
		{
			MUNum = 0;
			//地图合法性检测
			int yxnum = 0;
			int xznum = 0;
			int munum = 0;
			for(int i = 0; i < _MAP_S_ ; ++i)
			{
				map[i] = allmap[i + curstage * _MAP_S_];
				if(map[i] == _YX || map[i] == _QIU)
				{
					x = _XY_X(i);
					y = _XY_Y(i);
					yxnum++;
				}
				if(map[i] == _XZ || map[i] == _QIU)
					xznum++;
				if(map[i] == _MU)
					munum++;
				
			}
			if(yxnum != 1 || xznum != munum)
			{
				std::cout<<"地图非法，即将退出";
				system("pause");
				return;
			}
			MUNum = munum;
			GameState = _GAME_RUN;
		}
		else
		{
			//地图的绘制
			system("cls");
			for(int i = 0; i < _MAP_S_; ++i)
			{
				switch(map[i])
				{
				case _TL:std::cout<<"  ";break;
				case _ZA:std::cout<<"■";break;
				case _XZ:std::cout<<"□";break;
				case _MU:std::cout<<"木";break;
				case _YX:std::cout<<"人";break;
				case _KUN:std::cout<<"困";break;
				case _QIU:std::cout<<"囚";break;
				}
				if(_XY_X(i) == _MAP_W_ - 1)
					std::cout<<std::endl;
			}
			//游戏通关判断
			//bool tg = true;
			//for(int i = 0; i < _MAP_S_; ++i)
			//{
			//	if(map[i] == _MU)
			//	{
			//		tg = false;
			//		break;
			//	}
			//}
			//if(tg)
			if(MUNum == 0)
			{
				if(curstage == sizeof(allmap) / sizeof(map) - 1)
				{
					std::cout<<"通关了，回车重来，其他退出";
					if('\r' == _getch())
					{
						curstage = 0;
						GameState = _GAME_INIT;
						continue;
					}
					else
						break;
				}
				else
				{
					curstage++;
					GameState = _GAME_INIT;
					std::cout<<"进入下关";
					system("pause");
					continue;
				}
			}

			//获取按键控制
			int input = _getch();
			int x1 = -3;
			int y1 = -3;
			int x2 = -3;
			int y2 = -3;
			if((input == 'W'||input == 'w')&&y > 0)
			{
				x1 = x2 = x;
				y1 = y - 1;
				y2 = y - 2;
			}
			if((input == 'S'||input == 's')&& y < _MAP_H_ - 1)
			{
				x1 = x2 = x;
				y1 = y + 1;
				y2 = y + 2;
			}
			if((input == 'A'||input == 'a')&&x > 0)
			{
				y1 = y2 = y;
				x1 = x - 1;
				x2 = x - 2;
			}
			if((input == 'D'||input == 'd')&& x < _MAP_W_ - 1)
			{
				y1 = y2 = y;
				x1 = x + 1;
				x2 = x + 2;
			}
			if(input == 'R' || input == 'r')
			{
				GameState = _GAME_INIT;
			}

			//判断x1,y1上的游戏元素
			if(x1 != -3 && y1 != -3 && _IN_MAP(x1,y1) )
			{
				switch(map[_XY(x1,y1)])
				{
				case _ZA:break;
				case _TL:
					{
						map[_XY(x1,y1)] = _YX;
						if(map[_XY(x,y)] == _YX)
							map[_XY(x,y)] = _TL;
						else
							map[_XY(x,y)] = _XZ;
						x = x1;
						y = y1;
					}
					break;
				case _MU:
					{
						if(map[_XY(x2,y2)] == _TL)
						{
							map[_XY(x2,y2)] = _MU;
							map[_XY(x1,y1)] = _YX;
							if(map[_XY(x,y)] == _YX)
								map[_XY(x,y)] = _TL;
							else
								map[_XY(x,y)] = _XZ;
							x = x1;
							y = y1;
						}
						else if(map[_XY(x2,y2)] == _XZ)
						{
							map[_XY(x2,y2)] = _KUN;
							map[_XY(x1,y1)] = _YX;
							if(map[_XY(x,y)] == _YX)
								map[_XY(x,y)] = _TL;
							else
								map[_XY(x,y)] = _XZ;
							x = x1;
							y = y1;
							MUNum --;
						}
					}
					break;
				case _KUN:
					{
						if(map[_XY(x2,y2)] == _TL)
						{
							map[_XY(x2,y2)] = _MU;
							map[_XY(x1,y1)] = _QIU;
							if(map[_XY(x,y)] == _YX)
								map[_XY(x,y)] = _TL;
							else
								map[_XY(x,y)] = _XZ;
							x = x1;
							y = y1;
							MUNum++;
						}
						else if(map[_XY(x2,y2)] == _XZ)
						{
							map[_XY(x2,y2)] = _KUN;
							map[_XY(x1,y1)] = _QIU;
							if(map[_XY(x,y)] == _YX)
								map[_XY(x,y)] = _TL;
							else
								map[_XY(x,y)] = _XZ;
							x = x1;
							y = y1;
						}
					}
					break;
				case _XZ:
					{
						map[_XY(x1,y1)] = _QIU;
						if(map[_XY(x,y)] == _YX)
							map[_XY(x,y)] = _TL;
						else
							map[_XY(x,y)] = _XZ;
						x = x1;
						y = y1;
					}
					break;
				}
			
			}
		}
	}
	system("pause");
}