#include"eBullet.h"

CEbullet::CEbullet(int x1,int y1)
{
	x =x1;
	y =y1;
}
void CEbullet::run()
{
	y+=15;
}
int CEbullet::GetX()
{
	return x;
}
int CEbullet::GetY()
{
	return y;
}