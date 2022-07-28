#include <iostream>
#include "Test.h"
#include <iostream>

void main()
{
	//C c;
	//std::cout<<c.IsKindOf("C")<<std::endl;
	//std::cout<<c.IsKindOf("A")<<std::endl;
	//std::cout<<c.IsKindOf("CObject")<<std::endl;
	//std::cout<<c.IsKindOf("B")<<std::endl;

	A* p1 = (A*)_RUNTIME_CLASS::createClass("A");
	B* p2 = (B*)_RUNTIME_CLASS::createClass("B");
	C* p3 = (C*)_RUNTIME_CLASS::createClass("C");

	delete p1;
	delete p2;
	delete p3;

	system("pause");
}