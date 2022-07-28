#ifndef _USEBMP_
#define _USEBMP_
#include<windows.h>

HDC GetBmpDC(HWND hwnd,const char* bmpfile);
void DeleteBmpDC(HDC hdc);



#endif