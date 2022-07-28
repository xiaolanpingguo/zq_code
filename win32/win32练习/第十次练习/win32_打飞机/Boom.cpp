#include"Boom.h"
CBoom::CBoom(int x,int y)
{
	time =0;
	this->m_p.x = x;
	this->m_p.y = y;
}
bool CBoom::run()
{
	time+=1;
	if(time==8)
		return false;
	return true;	
}
int CBoom::GetTime()
{
	return time;
}

POINT CBoom::GetPoint()
{
	return m_p;
}