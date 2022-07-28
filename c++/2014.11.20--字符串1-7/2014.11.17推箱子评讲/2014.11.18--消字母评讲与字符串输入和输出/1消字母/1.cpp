#include<iostream>
#include<conio.h>
#include<time.h>

#define _MAP_W 20
#define _MAP_H 10
#define _MAP_S (_MAP_W * _MAP_H)

#define _XY(x,y) (x) + (y) * _MAP_W
#define _XY_X(i) (i) % _MAP_W
#define _XY_Y(i) (i) / _MAP_W

#define _CHAR_MIN 'a'
#define _CHAR_MAX 'c'
#define _CHAR_NONE 0

#define _GAME_INIT 0
#define _GAME_RUN  1

void main()
{
	srand(time(0));
	char map[_MAP_S];
	int x;
	int y;
	int GameState = _GAME_INIT;

	while(1)
	{
		if(_GAME_INIT == GameState)
		{
			for(int i = 0; i < _MAP_S; ++i)
			{
				map[i] = rand()%(_CHAR_MAX - _CHAR_MIN + 1) + _CHAR_MIN;
			}
			x = y = 0;
			GameState = _GAME_RUN;
		}
		else
		{
			system("cls");
			for(int i = 0; i < _MAP_S; ++i)
			{
				if(i == _XY(x,y))
				{
					if(map[i] == _CHAR_NONE)
						std::cout<<"*";
					else
						std::cout<<(char)(map[i] + ('A' - 'a'));
				}
				else
				{
					if(map[i] == _CHAR_NONE)
						std::cout<<" ";
					else
						std::cout<<map[i];
				}
				if(_XY_X(i) == _MAP_W - 1)
					std::cout<<std::endl;
			}

			//
			int input = _getch();

			if((input == 'W' || input == 'w') && y > 0)
				--y;
			if((input == 'S' || input == 's') && y < _MAP_H - 1)
				++y;
			if((input == 'A' || input == 'a') && x > 0)
				--x;
			if((input == 'D' || input == 'd') && x < _MAP_W - 1)
				++x;
			//消字母的循环判断过程及消字母的过程
			if(input == ' ' && map[_XY(x,y)] != _CHAR_NONE)
			{
				//辅助数组，辅助数组长度
				int help[_MAP_S];
				int helpLen = 0;
				//将当前光标的位置放入数组中
				help[0] = _XY(x,y);
				helpLen = 1;
				//设置一个遍历的起始终止下标
				int begin = 0,end = 0;
				//4个方向(上下左右)的偏移量
				int xdir[] = {0,0,-1,1};
				int ydir[] = {-1,1,0,0};
				while(1)
				{
					//得到没有发散的长度
					int curlen = helpLen;
					//循环发散新的下标
					for(int i = begin; i <= end; ++i)
					{
						int cx = _XY_X(help[i]);
						int cy = _XY_Y(help[i]);
						//循环上下左右方向
						for(int j = 0; j < 4;++j)
						{
							//得到该方向上新位置的坐标
							int dx = cx + xdir[j];
							int dy = cy + ydir[j];
							//判断是否出界
							if(dx >= 0 && dx < _MAP_W && dy >= 0 && dy < _MAP_H)
							{
								//判断是否和初始位置的值相同
								if(map[_XY(dx,dy)] == map[_XY(x,y)])
								{
									//判断是否在数组
									bool in = false;
									for(int k = 0; k < helpLen;++k)
									{
										if(help[k] == _XY(dx,dy))
										{
											in = true;
											break;
										}
									}
									if(!in)
										help[helpLen++] = _XY(dx,dy);
								}
							}
						}

					}
					//发散到新点，更新begin,end
					if(helpLen > curlen)
					{
						begin = curlen;
						end = helpLen - 1;
					}
					else
					{
						break;
					}
				}
				//消去字母
				for(int i = 0; i < helpLen; ++i)
				{
					map[help[i]] = _CHAR_NONE;
				}
				
				bool win = true;
				for(int i = 0; i < _MAP_S; ++i)
				{
					if(map[i]!= _CHAR_NONE)
					{
						win = false;
						break;
					}
				}
				if(win)
				{
					std::cout<<"回车重来，其他退出:";
					if('\r' == _getch())
					{
						GameState = _GAME_INIT;
					}
					else
						break;
				}
			}
		}
	}
	system("pause");
}

//相关的宏
//定义变量
//初始化变量
//游戏循环
//{
//输出
//输入
//逻辑
//}
//收尾