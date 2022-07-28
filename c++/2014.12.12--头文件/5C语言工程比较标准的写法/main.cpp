#include <iostream>
#include <conio.h>
#include "HBQ.h"


//C语言工程比较标准的写法
//C风格的模块
//我们把一组功能相近，内容相关的函数，
//全局变量看做是一个模块，我们用下面
//的方法来写这个模块
//01)一个CPP文件写这些模块的定义
//02)一个h文件写这些模块的声明
//03)一般来说，这两个文件名字相同，
//且cpp文件里面一般包含h文件
//我们使用这些模块只需要两件事情
//01)任何用到这个模块之前包含模块的h文件
//02)把模块的cpp文件放入工程参与编译

void main()
{
	Init();
	int x = 0,y = 0;
	while(1)
	{
		system("cls");
		for(int i = 0; i < _QP_S;++i)
		{
			if(_XY(x,y) == i)
			{
				switch(qp[i])
				{
				case _KZ:std::cout<<"◎";break;
				case _HZ:std::cout<<"□";break;
				case _BZ:std::cout<<"■";break;
				}
			}
			else
			{
				switch(qp[i])
				{
				case _KZ:std::cout<<"╋";break;
				case _HZ:std::cout<<"○";break;
				case _BZ:std::cout<<"●";break;
				}
			}
			if(_XY_X(i)== _QP_W - 1)
				std::cout<<std::endl;
		}
		int input = _getch();
		if((input == 'W'|| input == 'w')&& y > 0)
			--y;
		if((input == 'S'|| input == 's')&& y < _QP_H - 1)
			++y;
		if((input == 'A'|| input == 'a')&& x > 0)
			--x;
		if((input == 'D'|| input == 'd')&& x < _QP_W - 1)
			++x;

		if(input == 'U'||input == 'u')
			Play(x,y);
	}
	system("pause");
}
