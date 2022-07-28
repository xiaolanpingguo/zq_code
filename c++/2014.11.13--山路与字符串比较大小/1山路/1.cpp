#include<iostream>
#include<conio.h>

#define _MAP_W_ 25
#define _MAP_H_ 10
#define _MAP_S_ (_MAP_W_ * _MAP_H_)

#define _XY(x,y) (x) + (y) * _MAP_W_
#define _XY_X(i) (i) % _MAP_W_ 
#define _XY_Y(i) (i) / _MAP_W_

#define _KD 0
#define _SL 1

void main()
{
	//准备工作
	char map[_MAP_S_];
	int x;
	int y;
	for(int i = 0 ; i < _MAP_S_ - _MAP_W_; ++i)
	{
		map[i] = _KD;
	}
	for(int i = _MAP_S_ - _MAP_W_; i < _MAP_S_; ++i)
	{
		map[i] = _SL;
	}
	x = y = 0;
	//设置山路
	while(1)
	{
		//地图绘制
		system("cls");
		for(int i = 0 ;  i < _MAP_S_; ++i)
		{
			if(_XY(x,y) == i)
				std::cout<<"◎";
			else
			{
				if(map[i] == _KD)
					std::cout<<"□";
				else
					std::cout<<"▲";
			}
			if(_XY_X(i) == _MAP_W_ - 1)
				std::cout<<std::endl;
		}
		//获取按键
		int input = _getch();
		if((input == 'W'|| input == 'w')&& y > 0)
			--y;
		if((input == 'S'|| input == 's')&& y < _MAP_H_ - 1)
			++y;
		if((input == 'A'|| input == 'a')&& x > 0)
			--x;
		if((input == 'D'|| input == 'd')&& x < _MAP_W_ - 1)
			++x;
		if(input == ' ' && y > 0)
		{
			for(int i = 0; i < y; ++i)
			{
				map[_XY(x,i)] = _KD;
			}
			for(int i = y; i < _MAP_H_; ++i)
			{
				map[_XY(x,i)] = _SL;
			}
		}
		if(input == '\r')
		{
			x = 0;
			break;
		}
	}
	//重新设置y的位置
	for(y = _MAP_H_ - 1; y >= 0; y--)
	{
		if(map[_XY(x,y)] == _KD)
			break;
	}
	//游戏的运行部分
	while(1)
	{
		//游戏地图绘制
		system("cls");
		for(int i = 0; i < _MAP_S_ ; ++i)
		{
			if(_XY(x,y) == i)
			{
				std::cout<<"■";
			}
			else
			{
				if(map[i] == _KD)
					std::cout<<"□";
				else
					std::cout<<"▲";
			}
			if(_XY_X(i) == _MAP_W_ - 1)
				std::cout<<std::endl;
		}
		//获取按键
		int  input = _getch();
		if((input == 'A'|| input == 'a') && x > 0)
			--x;
		if((input == 'D'|| input == 'd') && x < _MAP_W_ - 1)
			++x;
		for(y = _MAP_H_ - 1; y >= 0; y--)
		{
			if(map[_XY(x,y)] == _KD)
				break;
		}
		if(input == '\r')
		{
			break;
		}
	}

	system("pause");
}