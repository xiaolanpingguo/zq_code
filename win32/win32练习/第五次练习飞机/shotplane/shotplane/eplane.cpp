#include "eplane.h"
#include<time.h>
#include<iostream>

void CEplane::run()
{
	switch(cp)
	{
	case _LEFT:
		{
			x-=5;
			y+=10;
			break;
		}
	case _MID:
		{
			y+=10;
			break;
		}
	case _RIGHT:
		{
			x+=5;
			y+=10;
			break;
		}
	}
}

CEplane::CEplane()
{
	cp = rand()%3;
	y = -80;
	x=rand()%250+100;
}

int CEplane::GetX()
{
	return x;
}
int CEplane::GetY()
{
	return y;
}