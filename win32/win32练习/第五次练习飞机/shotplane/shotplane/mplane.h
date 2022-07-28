#ifndef _MPLANE_
#define _MPLANE_
#include "plane.h"
#include<windows.h>


class CMplane:public CPlane
{
	int x;
	int y;
public:
	CMplane();
	int GetX();
	int GetY();
	void run(int x1,int y1);
};


#endif