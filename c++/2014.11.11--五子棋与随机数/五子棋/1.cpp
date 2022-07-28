#include <iostream>
#include <conio.h>

//棋盘大小及宽高相关宏
#define _MAP_W_  20
#define _MAP_H_  20
#define _MAP_S_  _MAP_W_ * _MAP_H_ 

//棋盘中下标与坐标关系的宏
#define _XY(x,y)   (x) + (y) * _MAP_W_
#define _XY_X(i)   (i) % _MAP_W_
#define _XY_Y(i)   (i) / _MAP_W_

//棋盘元素
#define _KZ 0
#define _HZ 1
#define _BZ 2

//游戏状态
#define _GAME_INIT 0
#define _GAME_RUN  1


void main()
{
	//设置游戏状态为初始化
	int GameState = _GAME_INIT;
	//游戏相关的:棋盘，光标等设置
	char qp[_MAP_S_];//棋盘
	int x;//光标位置
	int y;
	int qz;//当前的棋子

	while(1)
	{
		if(GameState == _GAME_INIT)
		{
			for(int i = 0; i < _MAP_S_; ++i)
			{
				qp[i] = _KZ;
			}
			x = y = 0;
			qz = _HZ;
			GameState = _GAME_RUN;
		}
		else
		{
			system("cls");
			//棋盘的绘制
			for(int i = 0; i < _MAP_S_;++i)
			{
				if(i == _XY(x,y))
				{
					switch(qp[i])
					{
					case _KZ:std::cout<<"◎";break;
					case _HZ:std::cout<<"□";break;
					case _BZ:std::cout<<"■";break;
					}
				}
				else
				{
					switch(qp[i])
					{
					case _KZ:
						{
							int cx = _XY_X(i);
							int cy = _XY_Y(i);
							if(cx == 0&&cy == 0)
							{
								std::cout<<"┏";
							}
							else if(cx == 0 && cy == _MAP_H_ - 1)
								std::cout<<"┗";
							else if(cx == _MAP_W_ - 1 && cy == 0)
								std::cout<<"┓";
							else if(cx == _MAP_W_ - 1 && cy == _MAP_H_ - 1)
								std::cout<<"┛";
							else if(cx > 0 && cx < _MAP_W_ - 1 && cy == 0)
								std::cout<<"┳";
							else if(cx > 0 && cx < _MAP_W_ - 1 && cy == _MAP_H_ - 1)
								std::cout<<"┻";
							else if(cy > 0 && cy < _MAP_H_ - 1 && cx == 0)
								std::cout<<"┣";
							else if(cy > 0 && cy < _MAP_H_ - 1 && cx == _MAP_W_ - 1)
								std::cout<<"┫";
							else
								std::cout<<"╋";


						}
						break;
					case _HZ:std::cout<<"○";break;
					case _BZ:std::cout<<"●";break;
					}
				}
				if(_XY_X(i) == _MAP_W_ - 1)
					std::cout<<std::endl;
			}

			//接受玩家输入
			int input = _getch();
			if((input == 'W'|| input == 'w') && y > 0)
				y--;
			if((input == 'S'|| input == 's')&& y < _MAP_H_ - 1)
				y++;
			if((input == 'A'|| input == 'a')&& x > 0)
				x--;
			if((input == 'D'|| input == 'd') && x < _MAP_W_ - 1)
				x++;
			if(input == ' ' && qp[_XY(x,y)] == _KZ)
			{
				qp[_XY(x,y)] = qz;
				char win = _KZ;

				for(int i = 0; i < 5; ++i)
				{
					//横向
					//竖向
					//左上到右下
					//左下到右上
					if(x - 4 + i >= 0 && x + i < _MAP_W_ - 1)
					{
						if(qp[_XY((x - 4 + i),y)] == qp[_XY((x - 3 + i),y)]
						&& qp[_XY((x - 3 + i),y)] == qp[_XY((x - 2 + i),y)]
						&& qp[_XY((x - 2 + i),y)] == qp[_XY((x - 1 + i),y)]
						&& qp[_XY((x - 1 + i),y)] == qp[_XY((x + i),y)])
						{
							win = qz;
							break;
						}
					}
					if(y - 4 + i >= 0 && y + i < _MAP_H_ - 1)
					{
						if(qp[_XY(x,(y - 4 + i))] == qp[_XY(x,(y - 3 + i))]
						&& qp[_XY(x,(y - 3 + i))] == qp[_XY(x,(y - 2 + i))]
						&& qp[_XY(x,(y - 2 + i))] == qp[_XY(x,(y - 1 + i))]
						&& qp[_XY(x,(y - 1 + i))] == qp[_XY(x,(y + i))])
						{
							win = qz;
							break;
						}
					}
					if(x - 4 + i >= 0 && x + i < _MAP_W_ - 1
					&& y - 4 + i >= 0 && y + i < _MAP_H_ - 1)
					{
						if(qp[_XY((x - 4 + i),(y - 4 + i))] == qp[_XY((x - 3 + i),(y - 3 + i))]
						&& qp[_XY((x - 2 + i),(y - 2 + i))] == qp[_XY((x - 3 + i),(y - 3 + i))]
						&& qp[_XY((x - 2 + i),(y - 2 + i))] == qp[_XY((x - 1 + i),(y - 1 + i))]
						&& qp[_XY((x - 1 + i),(y - 1 + i))] == qp[_XY((x + i),(y + i))])
						{
							win = qz;
							break;
						}
					}
					if(x - 4 + i >= 0 && x + i < _MAP_W_ - 1
					&& y + 4 - i >= 0 && y - i < _MAP_H_ - 1)
					{
						if(qp[_XY((x - 4 + i),(y + 4 - i))] == qp[_XY((x - 3 + i),(y + 3 - i))]
						&& qp[_XY((x - 2 + i),(y + 2 - i))] == qp[_XY((x - 3 + i),(y + 3 - i))]
						&& qp[_XY((x - 2 + i),(y + 2 - i))] == qp[_XY((x - 1 + i),(y + 1 - i))]
						&& qp[_XY((x - 1 + i),(y + 1 - i))] == qp[_XY((x + i),(y - i))])
						{
							win = qz;
							break;
						}
					}
				}
				if(win != _KZ)
				{
					//char sel;//选择 select
					do
					{
						std::cout<<(win == _HZ ? "黑":"白")<<"子胜利"<<std::endl;
						std::cout<<"重新游戏请按Y，退出游戏请按N"<<std::endl;
						input = _getch();
					}while(input != 'Y' && input != 'y' && input != 'N' && input != 'n');
					if(input == 'Y'|| input == 'y')
						GameState = _GAME_INIT;
					else
						break;
				}
				qz = (qz == _HZ)?_BZ:_HZ;

			}
		}
	}

	system("pause");
}