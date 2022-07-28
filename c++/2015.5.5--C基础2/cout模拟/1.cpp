#include <stdio.h>
#include <windows.h>
#include <iostream>

class ConsoleOutput
{
public:

	//为本类重载了<<运算符

	ConsoleOutput& operator << (int num)
	{
		printf("%d", num);
		return *this;
	}

	ConsoleOutput& operator << (char num)
	{
		printf("%c", num);
		return *this;
	}

	ConsoleOutput& operator << (double num)
	{
		printf("%f", num);
		return *this;
	}

	ConsoleOutput& operator << (const char* str)
	{
		printf("%s", str);
		return *this;
	}
};

ConsoleOutput cout;

void main()
{
	//int a;
	//printf("%d,%c,%f,%s,%p", 1, 'x', 3.14, "123abc", &a);

	cout<<1<<'x'<<3.14<<"123abc";

	system("pause");
}