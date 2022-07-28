#include "GameClass.h"
#include <iostream>
#include <conio.h>

class Game1 : public CGameClass
{
public:
	int x, y;
	virtual const char* name()
	{
		return "等待输入简单移动";
	}
	virtual void init()
	{
		x = 0;
		y = 0;
	}
	virtual void run()
	{
		while (1)
		{
			system("cls");
			for (int i = 0; i < 100; ++i)
			{
				if (i == x + y * 10)
					std::cout<<"◆";
				else
					std::cout<<"□";
				if (i % 10 == 9)
					std::cout<<std::endl;
			}
			int input = _getch();
			if ((input == 'w' || input == 'W') && y > 0)
				--y;
			if ((input == 's' || input == 'S') && y < 9)
				++y;
			if ((input == 'a' || input == 'A') && x > 0)
				--x;
			if ((input == 'd' || input == 'D') && x < 9)
				++x;
			if (input == 'q')
				break;
		}
	}
	virtual void end()
	{
		
	}
};

__declspec(dllexport) CGameClass* getGame()
{
	return new Game1;
}