#include <iostream>
#include "B.h"
#include "A.h"
void B::bf()
{
	std::cout<<"B::bf"<<std::endl;
}

void B::bb()
{
	a->af();
}