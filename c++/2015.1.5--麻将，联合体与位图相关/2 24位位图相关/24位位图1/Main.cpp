#include <iostream>
#include "24bitmap.h"

void main()
{
	BITMAPFILEHEADER* bmp1 = Open_24bmp("Autumn.bmp");
	int w, h;
	WH_24bmp(bmp1, &w, &h);

	//隔行扫描
	BITMAPFILEHEADER* bmp2 = Copy_24bmp(bmp1);
	for (int y = 0; y < h; y += 2)
	{
		for (int x = 0; x < w; x += 2)
		{
			_YS* p = color_24bmp(bmp2, x, y);
			p->r = p->g = p->b = 0;
		}
	}
	Save_24bmp("隔行扫描.bmp", bmp2);
	Close_24bmp(bmp2);

	//反色
	BITMAPFILEHEADER* bmp3 = Copy_24bmp(bmp1);
	for (int y = 0; y < h; ++y)
	{
		for (int x = 0; x < w; ++x)
		{
			_YS* p = color_24bmp(bmp2, x, y);
			p->r = ~p->r;
			p->g = ~p->g;
			p->b = ~p->b;
		}
	}
	Save_24bmp("反色.bmp", bmp3);
	Close_24bmp(bmp3);

	//灰度（灰色就是白到黑之间的均匀过渡）
	BITMAPFILEHEADER* bmp4 = Copy_24bmp(bmp1);
	for (int y = 0; y < h; ++y)
	{
		for (int x = 0; x < w; ++x)
		{
			_YS* p = color_24bmp(bmp2, x, y);
			unsigned char a = (p->r + p->g + p->b) / 3;
			p->r = p->g = p->b = a;
		}
	}
	Save_24bmp("灰度.bmp", bmp4);
	Close_24bmp(bmp4);


	Close_24bmp(bmp1);

	system("pause");
}

//Alpha混合公式