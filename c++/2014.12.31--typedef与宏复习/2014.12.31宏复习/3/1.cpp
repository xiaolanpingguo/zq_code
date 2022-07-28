#include<iostream>

struct _ABC
{
	int a,b,c;
}x,*y,z[3];//x是全局变量，*y是全局指针，z是全局数组

//上面的完全等同于这里的处理
//struct _ABC
//{
//	int a,b,c;
//};
//_ABC x;
//_ABC* y;
//_ABC z[3];

void main()
{
	
	system("pause");
}