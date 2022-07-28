#ifndef _GAMEINPUT_
#define _GAMEINPUT_
#include<windows.h>
class CGameInput
{
public:
	void run(HWND hwnd);
	void addMbullet();
	void boom();
};

#endif