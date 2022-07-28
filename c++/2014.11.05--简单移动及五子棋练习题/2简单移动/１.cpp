#include<iostream>
#include<conio.h>

#define _MAP_W 20 //地图宽
#define _MAP_H 20 //地图高
#define _MAP_S _MAP_W * _MAP_H //地图总大小

#define _KD 0//空地
#define _HERO 1 //英雄
//#define _ZA 2//障碍

#define _ZX(x,y) ((x) + (y) * _MAP_W) //坐标转下标
#define _XZ_X(i) ((i) % _MAP_W)//下标转坐标 x 
#define _XZ_Y(i) ((i)/_MAP_W) //下标转坐标 y 


void main()
{
	//定义地图
	int map[_MAP_S];
	//初始化英雄坐标
	int i_Herox = 1,i_Heroy = 1;

	while(1)
	{
		//初始化地图与英雄的位置
		for(int i = 0;i < _MAP_S;++i)
		{
			map[i] = _KD;
		}

		map[_ZX(i_Herox,i_Heroy)] = _HERO;

		system("cls");
		for(int i = 0;i < _MAP_S;++i)
		{
			switch(map[i])
			{
			case _KD:std::cout<<"□";break;
			case _HERO:std::cout<<"★";break;
			}
			if(_XZ_X(i) == _MAP_W - 1)
				std::cout<<std::endl;
		}
		int input = _getch();
		if((input == 'W'||input == 'w') && i_Heroy > 0)
			i_Heroy--;
		if((input == 'S' || input == 's') && i_Heroy < _MAP_H - 1)
			i_Heroy++;
		if((input == 'A'||input == 'a') && i_Herox > 0)
			i_Herox--;
		if((input == 'D' || input == 'd') && i_Herox < _MAP_W - 1)
			i_Herox++;

		if(input == 'Y' || input == 'y')
		{
			std::cout<<"游戏结束"<<std::endl;
			break;
		}
	}
	system("pause");
}

//游戏写作的过程
//01)定义相关的宏
//02)定义相关的变量
//03)初始化地图
//04)绘制地图
//05)按键响应
//06)判断，计算
//07)胜负判断
//08)游戏是否结束，是否重新开始