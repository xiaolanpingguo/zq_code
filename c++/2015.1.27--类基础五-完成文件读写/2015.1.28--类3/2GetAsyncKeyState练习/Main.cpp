#include <iostream>
#include <windows.h>
#include "GameInput.h"

CGameInput* gi = 0;

void f()
{
	int Key[] = {VK_UP, VK_DOWN, VK_LEFT, VK_RIGHT, VK_RETURN, VK_ESCAPE};
	gi = new CGameInput(Key, sizeof(Key) / sizeof(int));
}

void main()
{
	
	//CGameInput gi(Key, sizeof(Key) / sizeof(int));
	f();
	while (1)
	{
		gi->Run();

		if (_KS_KEEP_DOWN == gi->KeyState(0))
			std::cout<<"持续按下UP"<<std::endl;
		if (_KS_KEEP_DOWN == gi->KeyState(1))
			std::cout<<"持续按下DOWN"<<std::endl;
		if (_KS_KEEP_DOWN == gi->KeyState(2))
			std::cout<<"持续按下LEFT"<<std::endl;
		if (_KS_KEEP_DOWN == gi->KeyState(3))
			std::cout<<"持续按下RIGHT"<<std::endl;
		if (_KS_NOW_DOWN == gi->KeyState(4))
			std::cout<<"当前按下ENTER"<<std::endl;
		if (_KS_NOW_UP == gi->KeyState(5))
		{
			std::cout<<"当前抬起ESC"<<std::endl;
			break;
		}

		Sleep(33);
	}
	delete gi;

	system("pause");
}