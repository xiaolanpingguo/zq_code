#include <iostream>
#include "24bmp.h"

void main()
{
	BITMAPFILEHEADER* bfh0 = open_24bmp("0.bmp");
	int w, h;
	wh_24bmp(bfh0, &w, &h);

	//隔行扫描
	BITMAPFILEHEADER* bfh1 = copy_24bmp(bfh0);
	for (int y = 0; y < h; y += 2)
	{
		for (int x = 0; x < w; x += 2)
		{
			BGR* bgr = color_24bmp(bfh1, x, y);
			bgr->r = bgr->g = bgr->b = 0;
		}
	}
	save_24bmp(bfh1, "隔行扫描.bmp");
	free(bfh1);

	//反色
	BITMAPFILEHEADER* bfh2 = copy_24bmp(bfh0);
	for (int y = 0; y < h; ++y)
	{
		for (int x = 0; x < w; ++x)
		{
			BGR* bgr = color_24bmp(bfh2, x, y);
			bgr->r = ~bgr->r;
			bgr->g = ~bgr->g;
			bgr->b = ~bgr->b;
		}
	}
	save_24bmp(bfh2, "反色.bmp");
	free(bfh2);

	//灰度
	BITMAPFILEHEADER* bfh3 = copy_24bmp(bfh0);
	for (int y = 0; y < h; ++y)
	{
		for (int x = 0; x < w; ++x)
		{
			BGR* bgr = color_24bmp(bfh3, x, y);
			int color = (bgr->r + bgr->g + bgr->b) / 3;
			bgr->r = bgr->g = bgr->b = color;
		}
	}
	save_24bmp(bfh3, "灰度.bmp");
	free(bfh3);

	//缩放
	int dw, dh;
	std::cin>>dw>>dh;
	BITMAPFILEHEADER* bfh4 = create_24bmp(dw, dh);
	float blw = (float)w / dw;
	float blh = (float)h / dh;
	for (int y = 0; y < dh; ++y)
	{
		for (int x = 0; x < dw; ++x)
		{
			int sx = x * blw;
			int sy = y * blh;
			//BGR* bgr1 = color_24bmp(bfh4, x, y);
			//BGR* bgr2 = color_24bmp(bfh0, sx, sy);
			//*bgr1 = *bgr2;
			*color_24bmp(bfh4, x, y) = *color_24bmp(bfh0, sx, sy);
		}
	}
	save_24bmp(bfh4, "缩放.bmp");
	free(bfh4);

	//模糊
	int level;
	do
	{
		std::cin>>level;
	} while (level < 1 || level > 16);
	BITMAPFILEHEADER* bfh5 = copy_24bmp(bfh0);
	for (int y = 0; y < h; ++y)
	{
		for (int x = 0; x < w; ++x)
		{
			//得到当前的模糊化区域的所有颜色
			int r = 0, g = 0, b = 0;
			int x1 = x - level, y1 = y - level;
			int x2 = x + level, y2 = y + level;
			int pixel_num = 0;
			for (int cy = y1; cy <= y2; ++cy)
			{
				for (int cx = x1; cx <= x2; ++cx)
				{
					if (cx >= 0 && cx < w && cy >= 0 && cy < h)
					{
						BGR* color = color_24bmp(bfh0, cx, cy);
						r += color->r;
						g += color->g;
						b += color->b;
						pixel_num += 1;
					}
				}
			}

			BGR* bgr = color_24bmp(bfh5, x, y);
			bgr->r = r / pixel_num;
			bgr->g = g / pixel_num;
			bgr->b = b / pixel_num;
		}
	}
	save_24bmp(bfh5, "模糊化.bmp");
	free(bfh3);

	free(bfh0);
	system("pause");
}