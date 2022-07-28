#include<iostream>
#include<windows.h>
#include<conio.h>
#include<process.h>


//函数的调用方式分为3种：
//区别主要在于入栈的顺序，谁来清栈.
//01)_cdecl:参数从右向左入栈,调用者清栈
//02)_stdcall：参数从右向左入栈，被调用者清栈
//03)_fastcall:前两个大小 小于等于4byte的参数被传给ecx,edx寄存器
//其他参数从右向左入栈，被调用者清栈
unsigned int _stdcall music(void*)
{
	while(1)
	{
		Beep(200,300);
		Beep(300,300);
		Beep(400,300);
		Beep(500,300);
		Beep(600,300);
		Beep(700,300);
	}
}

void main()
{
	//将music函数用另外一个执行序列(线程)来执行，
	//和下面的执行时同时
	_beginthreadex(0,0,music,0,0,0);
	int x = 0,y = 0;
	while(1)
	{
		system("cls");
		for(int i = 0; i < 100; ++i)
		{
			std::cout<<((i == x + y * 10)?"◆":"□");
			if(i % 10 == 9)
				std::cout<<std::endl;
		}

		int input = _getch();
		if((input == 'W'||input == 'w') && y > 0)
			y--;
		if((input == 'S'||input == 's') && y < 9)
			y++;
		if((input == 'A'||input == 'a') && x > 0)
			x--;
		if((input == 'D'||input == 'd') && x < 9)
			x++;


	}
	system("pause");
}