#include "ConsoleRender.h"
#include <iostream>

//创建
CR createrCR(int w,int h)
{
	CR cr = (CR)malloc(sizeof(_CR));
	cr->w = w;
	cr->h = h;
	cr->p = (char*)malloc((cr->w * 2 + 5) * (cr->h + 2));
	char* q = cr->p;
	//设置上边框
	memcpy(q,"┏",2);q += 2;
	for(int i = 0; i < cr->w ;++i)
	{
		memcpy(q,"━",2);
		q += 2;
	}
	memcpy(q,"┓",2);
	q += 2;
	*q = '\n';q += 1;
	//设置中部
	for(int i = 0; i  < cr->h; ++i)
	{
		memcpy(q,"┃",2);q += 2 + cr->w * 2;
		memcpy(q,"┃",2);q += 2;
		*q = '\n';q += 1;
	}
	//设置下边框
	memcpy(q,"┗",2);q += 2;
	for(int i = 0; i < cr->w ;++i)
	{
		memcpy(q,"━",2);
		q += 2;
	}
	memcpy(q,"┛",2);
	q += 2;
	*q = 0;
	
	clearCR(cr);

	return cr;
}

//清空
void clearCR(CR cr)
{
	char* q = cr->p  + (cr->w * 2 + 5) + 2;
	for(int i = 0; i < cr->h; ++i)
	{
		for(int j = 0; j < cr->w * 2 ;++j)
			q[j]=' ';
		q += cr->w * 2 + 5;
	}
}

//设置指定位置
bool setCR(CR cr,int x,int y,const char* s)
{
	if(x < 0 || x >= cr->w || y < 0 || y >= cr->h ||!s)
		return false;
	if(strlen(s) > (cr->w - x) * 2)
		return false;
	char* q = cr->p + (cr->w * 2 + 5) + 2;
	memcpy(q + y * (cr->w * 2 + 5) + x * 2,s,strlen(s));
	return true;
}
void renderCR(CR cr)
{
	std::cout<<cr->p;
}
void destoryCR(CR cr)
{
	free(cr->p);
	free(cr);
}