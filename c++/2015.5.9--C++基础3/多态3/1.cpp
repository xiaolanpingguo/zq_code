#include <iostream>

//一般来说使用虚函数都是定义一个父类指针的容器，通过装载
//在这个容器中的父类指针去指向不同的子类对象

class A
{
public:
	int a;
};
class B : public A
{
public:
	int b;
};
class C : public A
{
public:
	int c;
};

class X
{
public:
	X(){std::cout<<"X构造"<<std::endl;}
	~X(){std::cout<<"X析构"<<std::endl;}
};
class Y : public X
{
public:
	Y(){std::cout<<"Y构造"<<std::endl;}
	~Y(){std::cout<<"Y析构"<<std::endl;}
};

class U
{
public:
	U(){std::cout<<"U构造"<<std::endl;}

	//设置继承体系下父类的析构为虚析构，那么就使得
	//在delete父类指针的时候，编译器能够正确的把从
	//子类到父类的所有析构都依次执行
	virtual ~U(){std::cout<<"U析构"<<std::endl;}
};
class V : public U
{
public:
	V(){std::cout<<"V构造"<<std::endl;}
	~V(){std::cout<<"V析构"<<std::endl;}
};

//Y y1; //直接定义静态对象，那么构造、析构的执行正确

void main()
{
	B b; b.a = 1; b.b = 2;
	C c; c.a = 3; c.c = 4;

	//父类对象数组被子类初始化之后，也无法保留
	//子类多出来的部分，相当于截取了子类中拥有
	//的父类的部分进行初始化或赋值给父类对象
	A x[] = {b, c};

	//y[0]、y[1]是A类型指针，分别指向了b、c的地址
	A* y[] = {&b, &c};

	//Y y2; //直接定义栈对象，那么构造、析构的执行正确

	//直接定义堆对象用当前类指针指向，那么构造、析构的执行正确
	//Y* y3 = new Y;
	//delete y3;

	//直接定义堆对象用当前类的父类指针指向，那么构造执行正确、析构执行错误
	X* y4 = new Y;
	delete y4; //因为delete的是父类指针，它就只会指向父类的析构

	U* p = new V;
	delete p;

	system("pause");
}