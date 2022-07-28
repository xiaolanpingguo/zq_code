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

	//缩放
	int dw, dh;
	do
	{
		std::cin>>dw>>dh;
	} while (dw < 1 || dh < 1);
	BITMAPFILEHEADER* bmp5 = Create_24bmp(dw, dh);
	float wbl = (float)w / (float)dw;
	float hbl = (float)h / (float)dh;
	for (int y = 0; y < dh; ++y)
	{
		for (int x = 0; x < dw; ++x)
		{
			_YS* p = color_24bmp(bmp5, x, y);
			
			//得到x、y位置按比例在原图中的颜色
			int sx = x * wbl, sy = y * hbl;
			_YS* q = color_24bmp(bmp1, sx, sy);

			//将找到的颜色赋值到位置上
			*p = *q;
		}
	}
	Save_24bmp("缩放.bmp", bmp5);
	Close_24bmp(bmp5);

	//模糊
	int level;
	do
	{
		std::cin>>level;
	} while (level < 1 || level > 8);
	BITMAPFILEHEADER* bmp6 = Copy_24bmp(bmp1);
	for (int y = 0; y < h; ++y)
	{
		for (int x = 0; x < w; ++x)
		{
			_YS* p = color_24bmp(bmp6, x, y);
			
			//采集周围多个颜色样本
			int r = 0, g = 0, b = 0, num = 0;
			for (int y1 = y - level; y1 <= y + level; ++y1)
			{
				for (int x1 = x - level; x1 <= x + level; ++x1)
				{
					if (y1 >= 0 && y1 < h && x1 >= 0 && x1 < w)
					{
						b += color_24bmp(bmp6, x1, y1)->b;
						g += color_24bmp(bmp6, x1, y1)->g;
						r += color_24bmp(bmp6, x1, y1)->r;
						num += 1;
					}
				}
			}
			p->r = r / num;
			p->g = g / num;
			p->b = b / num;
		}
	}
	Save_24bmp("模糊.bmp", bmp6);
	Close_24bmp(bmp6);

	//分量偏移
	int offsetr, offsetg, offsetb;
	do
	{
		std::cin>>offsetr>>offsetg>>offsetb;
	} while (offsetr < -255 || offsetr > 255 || offsetg < -255 || offsetg > 255 || offsetb < -255 || offsetb > 255);
	BITMAPFILEHEADER* bmp7 = Copy_24bmp(bmp1);
	for (int y = 0; y < h; ++y)
	{
		for (int x = 0; x < w; ++x)
		{
			_YS* p = color_24bmp(bmp6, x, y);

			if (p->r + offsetr < 0)
				p->r = 0;
			else if (p->r + offsetr > 255)
				p->r = 255;
			else
				p->r += offsetr;

			if (p->g + offsetg < 0)
				p->g = 0;
			else if (p->g + offsetg > 255)
				p->g = 255;
			else
				p->g += offsetg;

			if (p->b + offsetb < 0)
				p->b = 0;
			else if (p->b + offsetb > 255)
				p->b = 255;
			else
				p->b += offsetb;
		}
	}
	Save_24bmp("分量偏移.bmp", bmp7);
	Close_24bmp(bmp7);

	//颜色混合
	std::cout<<"颜色混合开始:";
	char fn[256];
	int x, y; //位置
	int alpha; //混合比例(0~255)
	int r, g, b; //透明颜色
	std::cin>>fn>>x>>y>>alpha>>r>>g>>b;
	BITMAPFILEHEADER* bmp8 = Open_24bmp(fn); //前景图
	BITMAPFILEHEADER* bmp9 = Copy_24bmp(bmp1); //背景图
	int qw, qh;
	WH_24bmp(bmp8, &qw, &qh);
	for (int xx = x; xx < x + qw; ++xx)
	{
		for (int yy = y; yy < y + qh; ++yy)
		{
			_YS* p = color_24bmp(bmp9, xx, yy);
			_YS* q = color_24bmp(bmp8, xx - x, yy - y);

			if (!(q->r == r && q->g == g && q->b == b))
			{
				p->r = (alpha / 255.0f) * q->r + (1.0f - alpha / 255.0f) * p->r;
				p->g = (alpha / 255.0f) * q->g + (1.0f - alpha / 255.0f) * p->g;
				p->b = (alpha / 255.0f) * q->b + (1.0f - alpha / 255.0f) * p->b;
			}
		}
	}
	Save_24bmp("颜色混合.bmp", bmp9);
	Close_24bmp(bmp9);
	Close_24bmp(bmp8);

	Close_24bmp(bmp1);

	system("pause");
}