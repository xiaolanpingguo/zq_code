#include <iostream>
#include <string>
#include <stdarg.h>
using namespace std;


//C式的变参打印
void c_Print(const char* szFormat, ...)
{
	// 根据传入的参数格式化字符串
	char strBuffer[1024] = {};
	va_list   arglist;

	// 处理变长参数
	va_start(arglist, szFormat);
	vsprintf(strBuffer, szFormat, arglist);
	va_end(arglist);

	// 在主界面中显示
	cout << strBuffer << endl;
}

//C式的加法处理
int c_Add(int count, ...)
{
	va_list ap;
	int sum = 0;

	va_start(ap, count);

	for (int i = 0; i < count; ++i)
	{
		int arg = va_arg(ap, int);
		sum += arg;
	}

	va_end(ap);

	return sum;
}

//在C++11中的变参打印
template <typename... TS>   // typename... TS为模板形参包，TS为模式
void cpp_Print(const char* s, TS ... args)  // TS... args为函数形参包，args为模式
{
	 printf(s, args...);
	 printf("\n");
}

//C++11中的加法处理
template<typename T1, typename... T2> 
int cpp_Add(T1 p, T2... arg)
{
	cout << "p:" << p << endl;
	int sum = p + cpp_Add(arg...);
	cout << "sum:" << sum << endl;

	return sum;
}

int cpp_Add()  //边界条件  
{
	return 0;
}

int main(int arg, char* args[])
{
	c_Print("C hello world：%d", 123456);
	cpp_Print("C++ hello world: %d", 123456);

	cout << c_Add(2, 20, 30) << endl;
	cout << cpp_Add(100, 300, 800) << endl;

	system("pause");
	return 0;
}