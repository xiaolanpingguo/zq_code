#include"mplane.h"

CMplane::CMplane()
{
	x = 220;
	y = 580;
}
int CMplane:: GetX()
{
	return x;
}
int CMplane:: GetY()
{
	return y;
}
void CMplane::run(int x1,int y1)
{
	x = x1;
	y = y1;
}