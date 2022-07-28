#include "UseBmp.h"


HDC GetBmpDC(HWND hwnd,const char* bmpfile)
{
	HBITMAP hbmp = (HBITMAP)LoadImage(0,bmpfile,IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
	if(!hbmp)
		return 0;
	//窗口主显示设备
	//HDC maindc = GetDC(HWND_DESKTOP);
	//得到主设备
	HDC maindc = GetDC(hwnd);

	//创建兼容显示设备
	HDC bmpdc = CreateCompatibleDC(maindc);

	//将新位图选入兼容设备中
	HBITMAP oldbmp = (HBITMAP)SelectObject(bmpdc,hbmp);

	//删除新位图，新位图选入到兼容设备后，兼容设备内部就完整的
	//复制了一份新位图的数据
	DeleteObject(hbmp);

	//删除老位图
	DeleteObject(oldbmp);

	//释放主设备
	ReleaseDC(hwnd,maindc);

	return bmpdc;
}

void DeleteBmpDC(HDC hdc)
{
	DeleteDC(hdc);
}