#ifndef _1_H_
#define _1_H_

template <typename T>
class p
{
	T t;
public:
	void f() //模板类中的内联函数
	{
		t = 0;
		std::cout<<t<<std::endl;
	}
	void ff();
};

template <typename T>
void p<T> ::ff()//模板类中的普通成员函数，直接将定义写在头文件中
{
	t = 0;
	std::cout<<t<<std::endl;
}

#endif