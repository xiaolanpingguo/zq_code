#include<iostream>

class XYZ1
{

};
class XYZ2
{
public :
	void f()
	{
		std::cout<<"Hello"<<std::endl;
	}
};

class XYZ3
{
public:
	char x;//[0]
	int z;//<1><2><3>[4][5][6][7]
	short y;//[8][9]<10><11>
};

class XYZ4
{
public:
	char x;
	int z;
	short y;
	void f()
	{
		std::cout<<"Hello"<<std::endl;
	}
};

//01)编译器会自动为空类(没有成员变量的类)
//添加一个无法访问也没有名字的char成员变量
//02)成员函数不算入sizeof大小
//03)类的成员变量也遵循内存对齐原则

void main()
{
	std::cout<<sizeof(XYZ1)<<std::endl;
	std::cout<<sizeof(XYZ2)<<std::endl;
	std::cout<<sizeof(XYZ3)<<std::endl;
	std::cout<<sizeof(XYZ4)<<std::endl;
	system("pause");
}
