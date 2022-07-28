#ifndef _MBULLET_
#define _MBULLET_
#include "Bullet.h"
class CMbullet : public CBullet
{
	int x;
	int y;
public :
	CMbullet(int x1,int y1);
	void run();
	int GetX();
	int GetY();
};

#endif