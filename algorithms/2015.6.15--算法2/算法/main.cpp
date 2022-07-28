#include <iostream>
#include <windows.h>
#include "FindPath.h"
#include "Sort.h"

#define _MAX_NUM 1000000
int a[_MAX_NUM];
int b[_MAX_NUM];

void main()
{
	for (int i = 0; i < _MAX_NUM; ++i)
		a[i] = rand();

	int t0 = GetTickCount();
	sort_quick<int>(a, 0, _MAX_NUM - 1);
	std::cout<<GetTickCount() - t0<<std::endl;

	int t1 = GetTickCount();
	sort_merge<int>(a, 0, _MAX_NUM - 1, b);
	std::cout<<GetTickCount() - t1<<std::endl;

	system("pause");
}