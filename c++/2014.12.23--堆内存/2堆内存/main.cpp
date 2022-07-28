#include<iostream>

//vs2005中全局变量理论上没有内存上限
//int a[1024 * 1024];

void main()
{
	//vs2005中栈内存的上限是1M
	//char a[1024 * 1000];
	
	//vs2005中堆内存理论上没有上限
	void* p = malloc(1024 * 1024 * 1024);

	free(p);
	
	system("pause");
}