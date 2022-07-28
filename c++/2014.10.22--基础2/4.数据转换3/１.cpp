#include <iostream>


void main()
{
	int a = 'x';
	short b = 'x';
	char c = 'x';
	//a,b,c中都存储的是整数120，但是在显示的时候
	//int和short都显示为整数，char显示为文字
	std::cout<<a<<std::endl;
	std::cout<<b<<std::endl;
	std::cout<<c<<std::endl;

	//现在a是int类型,如果是(char)a则类型是char类型
	std::cout<<(char)a<<std::endl;
	//上面(char)a的强制转换只是在上面这句代码起作用。
	//并不能改变a本身的数据类型
	std::cout<<a<<std::endl;

	std::cout<<(int)((char)a)<<std::endl;

	system("pause");
}