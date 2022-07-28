#include<iostream>
//24)得到指定位的函数
	//bool GetBit(void* p, int n);
	//若p开始的地址上的第n个位是1就返回真,是0就返回假
bool GetBit(const void* p, int n)
{
	char* q = (char*)p + n / 8;
	return (*q & (1 << (7 - n % 8))) != 0;
}
void main()
{
	
	system("pause");
}