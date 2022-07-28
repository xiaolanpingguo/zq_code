#include<iostream>
#include<conio.h>

void main()
{
	//无需回车的输入,获取用户输入的键值(按下的键的值)
	//int input = _getch();
	//返回的是一个整型值
	int input;
	while(1)
	{
		input = _getch();
		if(input == 'W'||input == 'w')
			std::cout<<"按下了W键"<<std::endl;
		if(input == 'A'||input == 'a')
			std::cout<<"按下了A键"<<std::endl;
		if(input == 'S'||input == 's')
			std::cout<<"按下了S键"<<std::endl;
		if(input == 'D'||input == 'd')
			std::cout<<"按下了D键"<<std::endl;

		if(input == ' ')
		{
			std::cout<<"按下了空格键"<<std::endl;
			break;
		}
	}
	//01)如果按下功能键，先返回0x00，再次调用才返回真正的键值
	//02)如果按下方向键，先返回0xe0，再次调用才返回真正的键值
	//03)如果输入的是双字节字符则返回2次
	//
	//

	system("pause");
}