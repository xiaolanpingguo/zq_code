#include<iostream>


void main()
{
	int a;
	std::cin>>a;

	//switch(a)
	//{
	//case 1:
	//	{
	//		std::cout<<"1"<<std::endl;
	//	}
	//	break;
	//case 2:
	//	{
	//		std::cout<<"2"<<std::endl;
	//	}
	//	break;
	//default:
	//	{
	//		std::cout<<"其他"<<std::endl;
	//	}
	//	break;
	//}

	if(a == 1)
	{
		std::cout<<"1"<<std::endl;
	}
	else if(a == 2)
	{
		std::cout<<"2"<<std::endl;
	}
	else
	{
		std::cout<<"其他"<<std::endl;
	}

	//if(A)
	//{
	//	B;
	//}
	//else if(C)
	//{
	//	D;
	//}
	//........
	//else
	//{
	//	F;
	//}
	//G;
	//执行表达式A，如果A的结果为真则执行表达式B;然后执行G；
	//如果表达式A为假，则执行C
	//如果C的结果为真则执行表达式D;然后执行G；
	//如果表达式C为假，则执行后面的else if()中的表达式，
	//如果一直为假，则最后执行F，然后执行G
	//如果有真，这执行该为真的判断所属的那个{}中的语句然后
	//执行G
	

	system("pause");
}