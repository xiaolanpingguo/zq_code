#include<iostream>
#include<time.h>
#include<windows.h>

#define _MAP_W 20
#define _MAP_H 20
#define _MAP_S (_MAP_W * _MAP_H)

void main()
{
	int x = 0;
	int y = 0;
	int bhx = -1;
	int bhy = -1;//变化坐标 -1代表没有变化
	int bh;//变化量
	bool zd;//增大标志
	while(1)
	{
		char map[_MAP_S] = {};
		map[x + y * _MAP_W] = 1;
		if(bhx != -1 && bhy != -1)
		{
			int x1 = bhx - bh;
			int y1 = bhy - bh;
			int x2 = bhx + bh;
			int y2 = bhy + bh;
			for(int i = x1;i <= x2; ++i)
			{
				map[i + y1 * _MAP_W] = 2;
				map[i + y2 * _MAP_W] = 2;
			}
			for(int i = y1; i <= y2;++i)
			{
				map[x1 + i * _MAP_W] = 2;
				map[x2 + i * _MAP_W] = 2;
			}
		}
			
		system("cls");
		for(int i = 0;i < _MAP_S; ++i)
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
		if(bhx != -1 && bhy != -1)
		{
			if(zd)
			{
				bh += 1;
				if(bhx - bh == 0 || bhy - bh == 0
				||bhx + bh == _MAP_W - 1
				||bhy + bh == _MAP_H - 1)
				zd = false;
			}
			else
			{
				bh -= 1;
				if(bh == -1)
					bhx = bhy = -1;
			}
		}
		if((GetAsyncKeyState('W') & 0x8000) && y > 0)
			--y;
		if((GetAsyncKeyState('S') & 0x8000) && y < _MAP_H - 1)
			++y;
		if((GetAsyncKeyState('A') & 0x8000) && x > 0)
			--x;
		if((GetAsyncKeyState('D') & 0x8000) && x < _MAP_W - 1)
			++x;

		if((GetAsyncKeyState(VK_SPACE)& 0x8000) &&(bhx == -1 && bhy == -1)
			&& x > 0 && x < _MAP_W - 1 && y > 0 && y < _MAP_H - 1)
		{
			bhx = x;
			bhy = y;
			bh = 0;
			zd = true;
		}

		Sleep(40);
	}
	
	system("pause");
}