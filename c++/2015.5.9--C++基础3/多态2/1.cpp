#include <iostream>

//一旦一个类体系下面有一个或一个以上的虚函数，那么
//编译器会自动在这个类体系中的所有类里面加上一个我
//们无法直接访问的虚函数指针__vfptr，这个虚函数指针
//指向一个虚函数表vftable，这个虚函数表中存储的是当
//前继承体系下本类中的虚函数地址，如果某个虚函数被
//子类重写了，那么该虚函数对应的虚函数表中的地址将
//被新的子类中的虚函数地址更新，只有当我们用类指针
//或类引用去调用虚函数的时候，编译器会将其处理成
//通过虚函数指针间接的调用

class A
{
public:
	void f1(){std::cout<<"A::f1"<<std::endl;}
	virtual void f2(){std::cout<<"A::f2"<<std::endl;}
};

void main()
{
	std::cout<<sizeof(A)<<std::endl;
	A a;

	system("pause");
}