#ifndef _BOOM_
#define _BOOM_
#include<windows.h>

class CBoom
{
	POINT m_p;
	int time;
public:
	CBoom(int x,int y);
	bool run();
	int GetTime();
	POINT GetPoint();
};

#endif