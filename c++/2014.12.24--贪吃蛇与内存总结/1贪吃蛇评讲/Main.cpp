#include <iostream>
#include <conio.h>
#include <windows.h>
#include "TCS.h"

void main()
{
	std::cout<<"即将开始贪吃蛇,";
	system("pause");

	//游戏初始化
	int df = 0;
	tcsInit(20, 10);

	while (1)
	{
		//获取游戏绘制数据
		const char* p = tcsMap();

		system("cls");
		for (int i = 0; i < 200; ++i)
		{
			switch (p[i])
			{
			case _KD: std::cout<<"□"; break;
			case _ZA: std::cout<<"■"; break;
			case _ST: std::cout<<"◆"; break;
			case _SS: std::cout<<"●"; break;
			case _GZ: std::cout<<"★"; break;
			}
			if (i % 20 == 20 - 1)
				std::cout<<std::endl;
		}
		std::cout<<"得分:"<<df<<std::endl;

		int input = _TCS_INPUT_NONE;
		if (GetAsyncKeyState(VK_UP) & 1)
			input = _TCS_INPUT_UP;
		if (GetAsyncKeyState(VK_DOWN) & 1)
			input = _TCS_INPUT_DOWN;
		if (GetAsyncKeyState(VK_LEFT) & 1)
			input = _TCS_INPUT_LEFT;
		if (GetAsyncKeyState(VK_RIGHT) & 1)
			input = _TCS_INPUT_RIGHT;

		//游戏运行
		int r = tcsRun(input);
		if (r == -1 || r == 0)
		{
			system("pause");

			char a;

			do
			{
				system("cls");
				std::cout<<"游戏失败,重新开始请按Y,退出游戏请按N:";
				std::cin>>a;
			} while (a != 'y' && a != 'Y' && a != 'n' && a != 'N');

			if (a == 'y' || a == 'Y')
			{
				//游戏重置
				tcsRestart();
				df = 0;
			}
			else
				break;
		}
		if (r == 2)
			df += 1;

		Sleep(150);
	}
}