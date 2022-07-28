#include <iostream>

extern int a1;
extern int b1;
void a2();
void b2();

#pragma comment(lib, "..\\debug\\makelib.lib")

void main()
{
	a1 = 100;
	a2();
	b1 = 101;
	b2();

	system("pause");
}