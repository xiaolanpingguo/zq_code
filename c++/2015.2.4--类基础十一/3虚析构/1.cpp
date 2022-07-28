#include <iostream>

class A
{
public:
	A()
	{
		std::cout<<"A构造"<<std::endl;
	}
	virtual ~A()//虚析构
	{
		std::cout<<"A析构"<<std::endl;
	}
};

class B : public A
{
public :
	B()
	{
		std::cout<<"B构造"<<std::endl;
	}
	~B()
	{
		std::cout<<"B析构"<<std::endl;
	}
};

class C
{
public:
	C()
	{
		std::cout<<"C构造"<<std::endl;
	}
	~C()
	{
		std::cout<<"C析构"<<std::endl;
	}
};

class D : public C
{
public :
	D()
	{
		std::cout<<"D构造"<<std::endl;
	}
	~D()
	{
		std::cout<<"D析构"<<std::endl;
	}
};




void main()
{
	//A* pA = new A;
	//delete pA;

	//B* pB = new B;
	//delete pB;

	//delete的是父类的指针，所以只会执行父类的
	//析构不会执行子类的析构
	C* pC = new D;
	delete pC;

	//这里能执行到子类的析构，因为A的析构是
	//虚析构
	A* pA1 = new B;
	delete pA1;

	
	system("pause");
}

//在继承体系下(特别是要使用多态)，
//一般会把最顶层的父类的析构设置为虚，
//这样能够保证delete父类指针的时候能
//正确的执行子类到父类的每一个析构函数
//只有析构可以是虚，构造不能为虚