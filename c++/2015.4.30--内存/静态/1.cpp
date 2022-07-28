#include <iostream>
#include <windows.h>
//a分配
//b分配
//y分配
//x分配
//z分配
//g分配
//g释放
//x释放
//y释放
//y分配
//x分配
//g分配
//g释放
//x释放
//y释放
//b释放
//z释放
//a释放
int f(int x, int y)
{
	static int z;
	z = x + y;
	int g = z;
	return g;
}
extern int a;
void main()
{
	int b = f(1, 2);
	a = b;
	a = f(3, 4);
	
	system("pause");
}
int a;