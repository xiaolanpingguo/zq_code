#ifndef _EBULLET_
#define _EBULLET_
#include "Bullet.h"
class CEbullet : public CBullet
{
	int x;
	int y;
public :
	CEbullet(int x1,int y1);
	void run();
	int GetX();
	int GetY();
};

#endif