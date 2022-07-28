#include"mBullet.h"

CMbullet::CMbullet(int x1,int y1)
{
	x=x1;
	y=y1;
}
void CMbullet::run()
{
	y-=15;
}

int CMbullet::GetX()
{
	return x;
}
int CMbullet::GetY()
{
	return y;
}