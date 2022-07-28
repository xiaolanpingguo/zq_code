#include<iostream>

#define _GAME_VERSION 2
//GameOutput只能在游戏版本1中才能使用
#if(_GAME_VERSION==1)

void GameOutput(int i)
{
	switch(i)
	{
	case 0:std::cout<<"□";break;
	case 1:std::cout<<"◆";break;
	case 2:std::cout<<"◇";break;
	case 3:std::cout<<"●";break;
	}
}

#endif

void main()
{
	GameOutput(1);
	system("pause");
}