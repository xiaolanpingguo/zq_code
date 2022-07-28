#include"UseBmp.h"

HDC GetBmpDC(HWND hwnd,const char* bmpfile)
{
	HBITMAP hbmp = (HBITMAP)LoadImageA(0,bmpfile,IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
	if(!hbmp)
		return 0;
	HDC maindc = GetDC(hwnd);
	HDC bmpdc =CreateCompatibleDC(maindc);
	
	HBITMAP oldbmp = (HBITMAP)SelectObject(bmpdc,hbmp);

	DeleteObject(hbmp);
	
	DeleteObject(oldbmp);
	
	ReleaseDC(hwnd,maindc);
	
	return bmpdc;
}
void DeleteBmpDC(HDC hdc)
{
	DeleteDC(hdc);
}
