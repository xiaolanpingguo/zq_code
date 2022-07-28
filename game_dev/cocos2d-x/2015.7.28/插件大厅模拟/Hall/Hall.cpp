#include <windows.h>
#include <iostream>
#include <vector>
#include <io.h>
#include "GameClass.h"

struct GAME
{
	HINSTANCE dll;
	CGameClass* game;
};
std::vector<GAME> game; //所有游戏

void findGame()
{
	//释放所有已经加载的游戏
	for (int i = 0; i < (int)game.size(); ++i)
	{
		FreeLibrary(game[i].dll);
		delete game[i].game;
	}
	game.clear();

	//搜索目录得到所有游戏
	_finddata_t fd;
	intptr_t fr = _findfirst("game\\*.dll", &fd);
	if (-1 != fr)
	{
		do
		{
			//得到游戏文件的路径
			char gd[256] = "game\\";
			strcat_s(gd, 256, fd.name);

			//打开游戏文件并读取游戏
			HINSTANCE gamedll = LoadLibraryA(gd);

			//得到getGame函数的首地址，注意这个函数
			//的名字已经被C++编译器修改为?getGame@@YAPAVCGameClass@@XZ
			FARPROC funadd = GetProcAddress(gamedll, "?getGame@@YAPAVCGameClass@@XZ");
			typedef CGameClass* (* funtype)(); //funtype是一个函数指针类型
			funtype fun = (funtype)funadd; //用funtype强转得到的首地址

			//调用函数得到游戏对象
			GAME g = {gamedll, (*fun)()};
			game.push_back(g);
			
		} while (0 == _findnext(fr, &fd));
	}
}

void main()
{
	while (1)
	{
		//得到所有游戏
		findGame();

		//打印游戏
		for (int i = 0; i < game.size(); ++i)
			std::cout<<i<<")"<<game[i].game->name()<<std::endl;

		//选择游戏
		int s;
		do
		{
			std::cout<<"请选择：";
			std::cin>>s;
		} while (s < 0 || s >= game.size());
		
		//进行游戏
		game[s].game->init();
		game[s].game->run();
		game[s].game->end();
	}

	system("pause");
}