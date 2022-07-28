#include <iostream>
#define _WIN32_WINNT 0x0500
#include <Winsock2.h>

void main()
{
	//得到控制台的窗口句柄
	HWND hwnd = GetConsoleWindow();

	//得到系统中的前台窗口的句柄
	while (1)
	{
		if (hwnd == GetForegroundWindow())
			std::cout<<"前台！";
		else
			std::cout<<"后台！";
		Sleep(33);
	}
	
	system("pause");
}