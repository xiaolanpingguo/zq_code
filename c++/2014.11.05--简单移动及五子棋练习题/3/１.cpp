#include<iostream>
#include<conio.h>

void main()
{
	//比如一副地图
	//□□□□□□□□□□
	//□□□□▲□□□□□
	//□□▲□□□□□□□
	//□□□□□□□▲□□
	//□□□□□□□□□□
	//□□□□▲□□□□□
	//□□□□□□□□□□
	//□□▲□□□□□□□
	//□□□□□□□▲□□
	//□□□□□□□□□□
	//可以用数组来存储上面的地图
	//用0表示空地，用1表示山,用合适的值来表示地形
	//定义一个大小合适的数组来存储
	//定义一个长度为100的数组来存储这幅地图，其中0为空地，1为山
	//3为边界
	int map[100] = 
	{
		2,0,3,3,3,3,3,3,3,3,
		0,0,0,0,1,0,0,0,0,3,
		3,0,1,0,0,0,0,0,0,3,
		3,0,0,0,0,0,0,1,0,3,
		3,0,0,0,0,0,0,0,0,3,
		3,0,0,0,1,0,0,0,0,3,
		3,0,0,0,0,0,0,0,0,3,
		3,0,1,0,0,0,0,0,0,3,
		3,0,0,0,0,0,0,1,0,3,
		3,3,3,3,3,3,3,3,3,3
	};
	int x = 0,y = 0;
	int x1 ,y1;
	while(1)
	{
		system("cls");
		//绘制地图
		for(int i = 0; i < 100; ++i)
		{
			//if(map[i] == 0)
			//	std::cout<<"□";
			//else if(map[i] == 1)
			//	std::cout<<"▲";
			switch(map[i])
			{
			case 0:std::cout<<"□";break;
			case 1:std::cout<<"▲";break;
			case 2:std::cout<<"○";break;
			case 3:std::cout<<"■";break;
			}
			if(i % 10 == 9)
				std::cout<<std::endl;
		}
		//std::cout<<"请输入要设置的山地的地图坐标:";
		//int x,y;
		//std::cin>>x>>y;
		//map[x + y * 10] = 1;
	
		int input = _getch();
		x1 = x;
		y1 = y;
		//0123
		if(input == 'W' || input == 'w')
		{
			y--;
		}
		if(input == 'S' || input == 's')
		{
			y++;
		}
		if(input == 'A' || input == 'a')
		{
			x--;
		}
		if(input == 'D' || input == 'd')
		{
			x++;
		}

		if((x >= 0 && x < 10)&&(y >= 0 && y < 10))
		{
			if(map[x + y * 10] == 3 || map[x + y * 10] == 1)
			{
				x = x1;
				y = y1;
			}
			else
			{
				map[x + y * 10] = 2;
				map[x1 + y1 * 10] = 0;
			}
		}
		else
		{
			x = x1;
			y = y1;
		}
	}
	system("pause");
}