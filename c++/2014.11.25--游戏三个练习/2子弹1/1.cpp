#include<iostream>
#include<time.h>
#include<windows.h>

#define _MAP_W 20
#define _MAP_H 10
#define _MAP_S (_MAP_W * _MAP_H)

#define _YX 1
#define _ZD 2
#define _KD 0

void main()
{
	int x = 0;
	int y = 0;
	char map[_MAP_S] = {};
	int zdx[_MAP_H];//10行子弹的x坐标
	bool moveleft[_MAP_H];//10行子弹的移动方向
	for(int i = 0; i < _MAP_H;++i)
		zdx[i] = -1;//-1表示本行没有子弹

	while(1)
	{
		//定义了一个地图数组。
		/*char map[_MAP_S] = {};*/
		map[x + y * _MAP_W] = _YX;
		for(int i = 0; i < _MAP_H ;++i)
		{
			if(zdx[i] != -1)
				map[zdx[i] + i * _MAP_W] = _ZD;
		}

		system("cls");

		for(int i = 0; i < _MAP_S; ++i)
		{
			switch(map[i])
			{
			case 0:std::cout<<"□";break;
			case 1:std::cout<<"●";break;
			case 2:std::cout<<"◆";break;
			}
			if(i % _MAP_W == _MAP_W - 1)
				std::cout<<std::endl;
		}
		
		for(int i = 0; i < _MAP_H; ++i)
		{
			if(zdx[i] != -1)
			{
				if(moveleft[i])
				{
					if(zdx[i] == 0)
						moveleft[i] = false;
					else
					{
						if(map[zdx[i] + i * _MAP_W] != _YX)
							map[zdx[i] + i * _MAP_W] = _KD;
						zdx[i] -= 1;
					}
				}
				else
				{
					if(zdx[i] == _MAP_W - 1)
						moveleft[i] = true;
					else 
					{
						if(map[zdx[i] + i * _MAP_W] != _YX)
							map[zdx[i] + i * _MAP_W] = _KD;
						zdx[i] += 1;
					}
				}
			}
		}

		int x1 = x;
		int y1 = y;

		if((GetAsyncKeyState('W') & 0x8000)
			&&y > 0)
			--y;
		if((GetAsyncKeyState('S') & 0x8000)
			&&y < _MAP_H - 1)
			++y;
		if((GetAsyncKeyState('A') & 0x8000)
			&&x > 0)
			--x;
		if((GetAsyncKeyState('D') & 0x8000)
			&&x < _MAP_W - 1)
			++x;

		if(map[x1 + y1 * _MAP_W] != _ZD)
			map[x1 + y1 * _MAP_W] = _KD;

		if(GetAsyncKeyState(VK_SPACE) & 0x8000)
		{
			if(zdx[y] != -1)
				zdx[y] = -1;
			else
			{
				zdx[y] = x;
				moveleft[y] = (x >= _MAP_W / 2);
			}
		}

		Sleep(40);

	}
	system("pause");
}