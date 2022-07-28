#include "MyString.h"

//作为构造函数，如果参数只有一个，那么是可以用下面的方式来写的
//A a(x);
//A a = x;

void main()
{
	CMyString ms1;
	CMyString ms2("abcdef");
	CMyString ms3 = "def";
	CMyString ms4 = ms3;
	ms4 = ms2; //完全等同于ms4.operator =(ms2);
	ms4 = "你好"; //完全等同于ms4.operator =("你好");
	ms4 = ms4 + ms3; //同类加法、同类赋值
	ms4 = ms4 + "世界"; //加法、同类赋值
	ms4 += ms3; //ms4.operator +=(ms3);
	ms4 += ms4; //ms4.operator +=(ms4);
	ms4 += "XYZ"; //ms4.operator +=("XYZ");
	ms4 += 'R'; std::cout<<ms4.GetString()<<std::endl;
	ms4[0] = 'T'; std::cout<<ms4.GetString()<<std::endl;
	ms4[1] = 'W'; std::cout<<ms4.GetString()<<std::endl;

	system("pause");
}