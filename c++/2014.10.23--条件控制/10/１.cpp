#include<iostream>

//break continue return goto

void main()
{
A:
	std::cout<<"A"<<std::endl;
	goto C;
B:
	std::cout<<"B"<<std::endl;
	goto D;
C:
	std::cout<<"C"<<std::endl;
	goto B;
D:
	std::cout<<"D"<<std::endl;
	system("pause");
}