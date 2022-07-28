#include "dds.h"
#include <iostream>

char map[_MAP_S];
bool input[9];
int hp;
int score;

//地图时间-记录老鼠存在的时间（出现攻击状态和消失的时刻）
int maptime[9];

void Game_Init()
{
	for(int i = 0; i < _MAP_S; ++i)
		map[i] = _KD;
	hp = 10;
	score = 0;
}

void Game_Logic()
{
	for(int i = 0; i < _MAP_S; ++i)
	{
		switch(map[i])
		{
		case _KD:
			{
				if(rand() % 100 == 0)
				{
					map[i] = _LS;
					maptime[i] = 0;
				}
			}
			break;
		case _LS:
			{
				if(input[i])
				{
					map[i] = _SW;
					maptime[i] = 0;
				}
				else
				{
					if(maptime[i] == 10)
					{
						map[i] = _GJ;
						maptime[i] = 0;
					}
					else
						maptime[i]++;
				}
			}
			break;
		case _GJ:
			{
				if(maptime[i] == 10)
				{
					hp -= 1;
					map[i] = _KD;
					maptime[i] = 0;
				}
				else
					maptime[i]++;
			}
			break;
		case _SW:
			{
				if(maptime[i] == 10)
				{
					score += 1;
					map[i] = _KD;
					maptime[i] = 0;
				}
				else
					maptime[i]++;
			}
			break;
		}
	}
}