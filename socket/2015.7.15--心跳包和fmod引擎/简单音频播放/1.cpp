#include <iostream>
#include <windows.h>
#include <conio.h>
#pragma comment(lib, "Winmm.lib")

void main()
{
	//同步函数（播放的声音不结束函数不返回）
	//Beep(1000, 500);

	PlaySoundA(
		"LoopyMusic.wav",
		0,
		SND_FILENAME | SND_LOOP | SND_ASYNC);
	//SND_FILENAME：表示第一个参数是文件名
	//SND_LOOP：循环播放
	//SND_SYNC：同步播放
	//SND_ASYNC：异步播放

	std::cout<<"请按任意键结束播放，";
	_getch();
	PlaySoundA(0, 0, 0);

	system("pause");
}