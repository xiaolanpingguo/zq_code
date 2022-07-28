#include <iostream>
#include "Test.h"

void main()
{
	C c;
	std::cout<<c.IsKindOf("C")<<std::endl;
	std::cout<<c.IsKindOf("A")<<std::endl;
	std::cout<<c.IsKindOf("CObject")<<std::endl;
	std::cout<<c.IsKindOf("B")<<std::endl;

	system("pause");
}