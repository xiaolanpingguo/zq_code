#include<iostream>
#include <windows.h>

//GetAsyncKeyState
//GetAsyncKeyState的返回值可以指示2种状况
//1)上一次调用本函数到本次调用该函数直接指定的
//键是否有被按下,如果有被按下则返回值的最低位
//1，反之为0
//2）当前指定键是否被按下，如果按下则返回值的
//最高位为1，反之为0

//short GetAsyncKeyState(int vkey)
//当前被按下其返回值
//1??????? ????????
//当前抬起其返回值
//0??????? ????????

//0x8000
//10000000 00000000
//如果要判断当前有没有被按下用if(返回值 & 0x8000)

//1
//00000000 00000001
//0 1
//如果刚才到现在之间被按下则返回值
//为 ???????? ???????1
//如果刚才到现在之间没有被按下则返回值
//为 ???????? ???????0

void main()
{
	while(1)
	{
		if(GetAsyncKeyState('A') & 0x8000)
			std::cout<<"A"<<std::endl;
		if(GetAsyncKeyState('B') & 1)
			std::cout<<"B"<<std::endl;

		Sleep(40);
	}
	system("pause");
}