#include "Mine.h"
#include <time.h>
#include <iostream>

//创建地图-w:宽,h：高，num:雷数
//地图地址
MINEGAME createMINEGAME(int w,int h,int num)
{
	if(w < 1 || h < 1 || num < 1)
		return 0;
	srand((unsigned int)time(0));
	MINEGAME mg = (MINEGAME)malloc(sizeof(_MINE_GAME));
	mg->w = w;
	mg->h = h;
	mg->num = num;
	mg->map = (_MINE*)malloc(sizeof(_MINE) * mg->w * mg->h);
	mg->help = (int*)malloc(sizeof(int) * mg->w * mg->h);
	//处理地图
	//得到地图大小
	int s = mg->w * mg->h;
	for(int i = 0 ; i < s; ++i)
	{
		mg->map[i].is_mine = false;
		mg->map[i].is_open = false;
	}

	//放雷
	int* p = (int*)malloc(sizeof(int) * s);
	for(int i = 0; i < s;++i)
		p[i] = i;
	for(int i = 0; i < num;++i)
	{
		int index = rand() % s;
		mg->map[p[index]].is_mine = true;
		//mg->map[index].is_mine = true;
		p[index] = p[s - 1];
		s -= 1;
	}
	free(p);

	//计算每个格子周围的雷数
	s = mg->w * mg->h;

	int xd[] = {0,1,1,1,0,-1,-1,-1};
	int yd[] = {-1,-1,0,1,1,1,0,-1};
	
	for(int i = 0; i < s;++i)
	{
		mg->map[i].mine_num = 0;
		int x = i % mg->w,y = i / mg->w;
		for(int j = 0; j < 8;++j)
		{
			int cx = x + xd[j];
			int cy = y + yd[j];
			if(cx >= 0 && cx < mg->w 
			&& cy >= 0 && cy < mg->h)
			{
				if(mg->map[cx + cy * mg->w].is_mine)
					mg->map[i].mine_num += 1;
			}
		}
	}
	return mg;
}

//MINEGAME的地址
//返回-1,0,1代表失败，正常，通关
int playMINEGAME(MINEGAME mg,int x,int y)
{
	if(mg->map[x + y * mg->w].is_mine)
		return -1;
	//开启格子
	mg->help[0] = x + y * mg->w;
	int help_len = 1;//辅助数组当前有效数据长度
	//循环起始，终止下标
	int begin = 0,end = 0;
	//开地图块
	int xd[] = {0,1,1,1,0,-1,-1,-1};
	int yd[] = {-1,-1,0,1,1,1,0,-1};
	while(1)
	{
		int cur_help_len = help_len;
		for(int i = begin ; i <= end;++i)
		{
			//必须是周围雷数为0才开启
			if(mg->map[mg->help[i]].mine_num == 0)
			{
				int x = mg->help[i] % mg->w;
				int y = mg->help[i] / mg->w;
				//得到(x,y)周围8个方向
				for(int j = 0; j < 8 ;++j)
				{
					int cx = x + xd[j];
					int cy = y + yd[j];
					if(cx >= 0 && cx < mg->w 
					&& cy >= 0 && cy < mg->h)
					{
						//不是雷
						if(!mg->map[cx + cy * mg->w].is_mine)
						{
							bool no = true;
							for(int k = 0; k < help_len;++k)
							{
								if(mg->help[k] == cx + cy * mg->w)
								{
									no = false;
									break;
								}
							}
							if(no)
								mg->help[help_len++] = cx + cy * mg->w;
						}
					}
				}
			}
		}
		if(cur_help_len == help_len)
			break;
		else
		{
			begin = cur_help_len;
			end = help_len - 1;
		}
	}

	for(int i = 0 ; i < help_len;++i)
		mg->map[mg->help[i]].is_open = true;

	//判断通关
	for(int i = 0; i < mg->w * mg->h ; ++i)
	{
		if(!mg->map[i].is_mine && !mg->map[i].is_open)
			return 0;
	}
	return 1;
}

//结束
void endMINEGAME(MINEGAME mg)
{
	free(mg->help);
	free(mg->map);
	free(mg);
}