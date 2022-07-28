#include "GameClass.h"
#include <iostream>
#include <windows.h>

class Game2 : public CGameClass
{
public:
	int x, y;
	virtual const char* name()
	{
		return "非等待输入简单移动";
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
			for (int i = 0; i < 400; ++i)
			{
				if (i == x + y * 20)
					std::cout<<"◆";
				else
					std::cout<<"□";
				if (i % 20 == 19)
					std::cout<<std::endl;
			}
			if ((::GetAsyncKeyState(VK_UP) & 0x8000) && y > 0)
				--y;
			if ((::GetAsyncKeyState(VK_DOWN) & 0x8000) && y < 19)
				++y;
			if ((::GetAsyncKeyState(VK_LEFT) & 0x8000) && x > 0)
				--x;
			if ((::GetAsyncKeyState(VK_RIGHT) & 0x8000) && x < 19)
				++x;
			if (GetAsyncKeyState(VK_ESCAPE) & 1)
				break;
			Sleep(33);
		}
	}
	virtual void end()
	{
		
	}
};

__declspec(dllexport) CGameClass* getGame()
{
	return new Game2;
}