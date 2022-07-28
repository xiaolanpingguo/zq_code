#include<iostream>
#include<time.h>
#include "TCS.h"


//地图
char map[_MAP_MAX_W * _MAP_MAX_H];

//记录蛇长的数组
int she[_MAP_MAX_W * _MAP_MAX_H];

//蛇长
int she_num = 0;
//蛇方向
int she_dir = 0;

//障碍
int zhangai[_MAP_MAX_W * _MAP_MAX_H];
//障碍数量
int zhangai_num = 0;

//果子
int gz;

//是否初始化成功
bool init = false;

int w;

int h;

//贪吃蛇初始化函数
//mapW:地图宽
//mapH:地图高
//返回:成功或失败(宽、高不合符要求将导致失败)
bool tcsInit(int mapW, int mapH)
{
	srand((unsigned int)time(0));

	if(mapW < _MAP_MIN_W || mapW >_MAP_MAX_W 
		|| mapH <_MAP_MIN_H || mapH >_MAP_MAX_H)
		return false;
	else
	{
		::w = mapW;
		::h = mapH;

		she[0] = rand() % (mapW * mapH);
		she_num = 1;
		she_dir = rand() % 4;

		zhangai_num = (mapW * mapH) / 40;

		for(int i = 0; i < zhangai_num; ++i)
		{
			int suiji = rand() % (mapW * mapH);
			bool chongfu = false;
			for(int j = 0; j < i; ++j)
			{
				if(suiji == zhangai[j])
				{
					chongfu = true;
					break;
				}
			}
			if(chongfu)
				i--;
			else
				zhangai[i] = rand() % (mapW * mapH);
		}
		gz = rand() % (mapW * mapH);
		return init = true;
	}
}

//贪吃蛇运行函数
//input:输入,_TCS_INPUT_NONE、_TCS_INPUT_UP、
//_TCS_INPUT_DOWN、_TCS_INPUT_LEFT、
//_TCS_INPUT_RIGHT分别代表
//无输入、上、下、左、右
//返回:-3代表没有初始化、
//-2代表输入错误、
//-1代表蛇头咬了蛇身、
//0代表撞着了障碍
//1代表正常
//2代表吃了一个果子
int tcsRun(int input)
{
	if(!init)
		return -3;
	if(input < _TCS_INPUT_NONE || input > _TCS_INPUT_RIGHT)
		return -2;

	//方向
	if(input != _TCS_INPUT_NONE)
	{
		switch(she_dir)
		{
		case 0:
		case 1:
			{
				if(input == _TCS_INPUT_LEFT || input == _TCS_INPUT_RIGHT)
					she_dir = input - 1;
			}
			break;
		case 2:
		case 3:
			{
				if(input == _TCS_INPUT_UP || input == _TCS_INPUT_DOWN)
					she_dir = input - 1;
			}
			break;
		}
	}

	//蛇头与果子碰撞
	bool df = false;

	if(she[0] == gz)
	{
		gz = rand() % (w * h);
		she_num += 1;
		df = true;
	}

	//蛇头和蛇身
	for(int i = 1; i < she_num ; ++i)
	{
		if(she[0] == she[i])
			return -1; 
	}

	//蛇头和障碍
	for(int i = 0; i < zhangai_num ; ++i)
	{
		if(she[0] == zhangai[i])
			return 0; 
	}

	//蛇身移动
	for(int i = she_num - 1;i > 0;--i)
		she[i] = she[i - 1];
	//蛇头移动
	int x = she[0] % w;
	int y = she[0] / w;

	switch(she_dir)
	{
	case 0:y = ((y == 0) ? h - 1: y - 1);break;
	case 1:y = ((y == h  - 1) ? 0: y + 1);break;
	case 2:x = ((x == 0) ? w - 1: x - 1);break;
	case 3:x = ((x == w  - 1) ? 0: x + 1);break;
	}

	she[0] = x + y * w;
	return df ? 2 : 1;
}

//贪吃蛇重置函数
//返回:成功或失败(没有初始化将导致失败)
bool tcsRestart()
{
	return tcsInit(w,h);
}

//贪吃蛇得到地图函数
//返回:0或地图数组首地址,
//用于绘制(没有初始化将导致返回0)
const char* tcsMap()
{
	if(!init)
		return 0;
	for(int i = w * h;i >= 0;--i)
		map[i] = _KD;
	for(int i = 0; i < zhangai_num;++i)
		map[zhangai[i]] = _ZA;
	map[she[0]] = _ST;
	for(int i = 1;i < she_num;++i)
		map[she[i]] = _SS;
	map[gz] = _GZ;
	return map;
}