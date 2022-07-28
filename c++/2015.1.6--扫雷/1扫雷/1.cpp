#include<iostream>
#include "Mine.h"
#include "ConsoleRender.h"
#include <conio.h>

#define _GAME_W 20
#define _GAME_H 20
#define _GAME_N 10

void main()
{
	const char* s1[] = {"１","２","３","４","５","６","７","８"};

	const char* s2[] = {"①","②","③","④","⑤","⑥","⑦","⑧"};

	MINEGAME mg = createMINEGAME(_GAME_W,_GAME_H,_GAME_N);
	CR cr = createrCR(_GAME_W,_GAME_H);
	int x = 0,y = 0;
	while(1)
	{
		system("cls");
		for(int i = 0; i < _GAME_W*_GAME_H;++i)
		{
			int cx = i % _GAME_W;
			int cy = i / _GAME_W;
			if(cx == x && cy == y)
			{
				if(mg->map[i].is_open)
				{
					if(mg->map[i].mine_num > 0)
						setCR(cr,cx,cy,s2[mg->map[i].mine_num - 1]);
					else
						setCR(cr,cx,cy,"○");
				}
				else
					setCR(cr,cx,cy,"□");
			}
			else
			{
				if(mg->map[i].is_open)
				{
					if(mg->map[i].mine_num > 0)
						setCR(cr,cx,cy,s1[mg->map[i].mine_num - 1]);
					else
						setCR(cr,cx,cy,"□");
				}
				else
					setCR(cr,cx,cy,"■");
			}
		}
		renderCR(cr);
		int input = _getch();
		if((input == 'w' ||input == 'W') && y  > 0)
			--y;
		if((input == 's' ||input == 'S') && y  < _GAME_H - 1)
			++y;
		if((input == 'a' ||input == 'A') && x  > 0)
			--x;
		if((input == 'D' ||input == 'd') && x  < _GAME_W - 1)
			++x;

		if(input == ' ')
		{
			int r = playMINEGAME(mg,x,y);
			if(r == -1)
			{
				std::cout<<"游戏失败";
				break;
			}
			else if(r == 1)
			{
				std::cout<<"游戏通关";
				break;
			}
		}
	}
	destoryCR(cr);
	endMINEGAME(mg);
	system("pause");
}