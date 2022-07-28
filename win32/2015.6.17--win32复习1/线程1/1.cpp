#include <iostream>
#include <conio.h>
#include <windows.h>
#include <process.h>

unsigned int __stdcall music(void* p)
{
	while (1)
	{
		Beep(256, 200);
		Beep(356, 200);
		Beep(456, 200);
		Beep(556, 200);
		Beep(656, 200);
	}
}

void main()
{
	//开启一个线程去执行指定的函数，该函数
	//必须返回unsigned int，必须是标准调用
	//，必须是有一个void*形参
	_beginthreadex(
		0,
		0,
		music,
		0,
		0,
		0);

	int x = 0, y = 0;
	while (1)
	{
		system("cls");

		for (int i = 0; i < 100; ++i)
		{
			if (x + y * 10 == i)
				std::cout<<"◆";
			else
				std::cout<<"□";
			if (i % 10 == 9)
				std::cout<<std::endl;
		}

		//if ((GetAsyncKeyState('W') & 1) && y > 0)
		//	--y;
		//if ((GetAsyncKeyState('S') & 1) && y < 9)
		//	++y;
		//if ((GetAsyncKeyState('A') & 1) && x > 0)
		//	--x;
		//if ((GetAsyncKeyState('D') & 1) && x < 9)
		//	++x;

		int input = _getch();
		if ((input == 'W' || input == 'w') && y > 0)
			--y;
		if ((input == 'S' || input == 's') && y < 9)
			++y;
		if ((input == 'A' || input == 'a') && x > 0)
			--x;
		if ((input == 'D' || input == 'd') && x < 9)
			++x;
	}
}