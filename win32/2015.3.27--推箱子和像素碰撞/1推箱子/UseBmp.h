#ifndef _USEBMP_H_
#define _USEBMP_H_
#include <windows.h>


HDC GetBmpDC(HWND hwnd,const char* bmpfile);
void DeleteBmpDC(HDC hdc);

#endif