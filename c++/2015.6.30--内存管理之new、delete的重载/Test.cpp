#include <iostream>

class A
{
public:
	A(){std::cout<<"A构造"<<std::endl;}
	~A(){std::cout<<"A析构"<<std::endl;}
};

void main()
{
	//new 类型;
	//上面的表达式被成为new运算表达式，new运算表达式会执行两个处理
	//1）去寻找全局的new运算符来分配堆内存
	//2）执行构造

	//delete 地址;
	//上面的表达式被成为delete运算表达式，delete运算表达式会执行两个处理
	//1）执行析构
	//2）去寻找全局的delete运算符来释放堆内存

	int* p = new int;
	int* q = new int[2];
	delete p;
	delete [] q;

	A* r = new A;
	delete r;

	system("pause");
}