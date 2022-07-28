#include "A.h"
#include "B.h"
#include <iostream>

void A::af()
{
	std::cout<<"A::af"<<std::endl;
}


void A::aa()
{
	b->bf();
}