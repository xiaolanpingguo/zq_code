#ifndef _EPLANE_
#define _EPLANE_
#include "plane.h"

#define _LEFT 0
#define _MID 1
#define _RIGHT 2

class CEplane:public CPlane
{
	int x;
	int y;
	int cp;
public:
	CEplane();
	int GetX();
	int GetY();
	void run();
};


#endif