#ifndef _CONSOLERENDER_H_
#define _CONSOLERENDER_H_

typedef struct _CR
{
	int w,h;
	char* p;
}* CR;

CR createrCR(int w,int h);
void clearCR(CR cr);
bool setCR(CR cr,int x,int y,const char* s);
void renderCR(CR cr);
void destoryCR(CR cr);

#endif