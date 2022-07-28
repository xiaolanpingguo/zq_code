#include <iostream>

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

class C : public B
{

};
class D : public C
{

};





void main()
{
	A a;
	B b;
	C c;
	D d;
	b = c;
	a = c;
	a = d;
	//d = c;
	system("pause");
}