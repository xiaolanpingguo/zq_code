#include <iostream>
#include <windows.h>

void main()
{
	//GetAsyncKeyState()

	while(1)
	{
		//字母键的检测必须是该字母的大写的字面常量
		if(GetAsyncKeyState('A') & 0x8000)
			std::cout<<"A"<<std::endl;
		if(GetAsyncKeyState('1') & 0x8000)
			std::cout<<"大键盘1"<<std::endl;
		if(GetAsyncKeyState(VK_NUMPAD1) & 0x8000)
			std::cout<<"小键盘1"<<std::endl;
		if(GetAsyncKeyState(VK_RETURN) & 0x8000)
			std::cout<<"回车键"<<std::endl;
		if(GetAsyncKeyState(VK_SPACE) & 0x8000)
			std::cout<<"空格键"<<std::endl;
		if(GetAsyncKeyState(VK_ESCAPE) & 0x8000)
			std::cout<<"Esc键"<<std::endl;
		if(GetAsyncKeyState(VK_UP) & 0x8000)
			std::cout<<"UP键"<<std::endl;
		if(GetAsyncKeyState(VK_DOWN) & 0x8000)
			std::cout<<"DOWN键"<<std::endl;
		if(GetAsyncKeyState(VK_LEFT) & 0x8000)
			std::cout<<"LEFT键"<<std::endl;
		if(GetAsyncKeyState(VK_RIGHT) & 0x8000)
			std::cout<<"RIGHT键"<<std::endl;

		//使当前的程序休息指定的毫秒数
		//帧指一秒内执行多少次游戏循环
		Sleep(200);
	}
	system("pause");
}