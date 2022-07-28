#include <iostream>
#include <conio.h>

#define _MAP_W 10
#define _MAP_H 20
#define _MAP_S _MAP_W * _MAP_H

#define _XY(x,y) (x) + (y) * _MAP_W
#define _XY_X(i)  (i) % _MAP_W
#define _XY_Y(i)  (i) / _MAP_W

#define _TL 0
#define _ZA 1
#define _XZ 2
#define _MU 3
#define _YX 4
#define _KUN 5
#define _QIU 6

#define _GAME_INIT 0
#define _GAME_RUN  1

void main()
{
	char map[_MAP_S] = 
	{
		1,1,1,1,1,1,1,1,1,1,
		1,0,0,0,0,0,0,0,0,1,
		1,0,4,0,0,0,0,0,0,1,
		1,0,3,3,1,1,1,2,0,1,
		1,0,0,0,0,0,0,0,0,1,
		1,1,0,0,2,1,1,0,0,1,
		1,1,1,1,1,1,0,0,0,1,
		1,0,0,0,1,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,1,
		1,1,1,1,1,1,1,1,1,1,

		1,1,1,1,1,1,1,1,1,1,
		1,0,0,0,0,0,0,0,0,1,
		1,0,4,0,0,0,0,0,0,1,
		1,0,3,3,1,1,1,2,0,1,
		1,0,0,0,0,0,0,0,0,1,
		1,1,0,0,2,0,1,5,0,1,
		1,1,1,1,1,0,0,0,0,1,
		1,0,0,0,1,0,3,0,0,1,
		1,0,0,0,0,0,0,0,0,1,
		1,1,1,1,1,1,1,1,1,1
	};
	char map1[100];
	int x;
	int y;
	int GameState = _GAME_INIT;
	int ganka = 1;
	while(1)
	{
		if(GameState == _GAME_INIT)
		{
			//地图数组map1的赋值处理



			//得到英雄的位置
			for(int i = 0; i < 100; ++i)
			{
				if(map1[i] == _YX || map1[i] == _QIU)
				{
					x = _XY_X(i);
					y = _XY_Y(i);
					break;
				}
			}
			//更改游戏状态
			GameState = _GAME_RUN;
		}
		else
		{
			system("cls");
			for(int i = 0 ; i < 100 ; ++i)
			{
				switch(map1[i])
				{
				case _TL:std::cout<<"  ";break;
				case _ZA:std::cout<<"■";break;
				case _XZ:std::cout<<"□";break;
				case _MU:std::cout<<"木";break;
				case _YX:std::cout<<"人";break;
				case _KUN:std::cout<<"困";break;
				case _QIU:std::cout<<"囚";break;
				}
				if(_XY_X(i) == _MAP_W - 1)
					std::cout<<std::endl;
			}
			int input = _getch();

			if((input == 'W'||input == 'w')&&y > 0)
			{
				
			}
		}
	}



	system("pause");
}