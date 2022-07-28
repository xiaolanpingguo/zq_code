#include "24bmp.h"
#include <iostream>

BITMAPFILEHEADER* open_24bmp(const char* bmp)
{
	FILE* pf = 0;
	fopen_s(&pf, bmp, "rb");
	if (!pf)
		return 0;
	fseek(pf, 0, SEEK_END);
	int fs = ftell(pf);
	rewind(pf);
	BITMAPFILEHEADER* bfh = (BITMAPFILEHEADER*)malloc(fs);
	fread(bfh, 1, fs, pf);
	fclose(pf);
	return bfh;
}

BITMAPFILEHEADER* copy_24bmp(BITMAPFILEHEADER* bfh)
{
	BITMAPFILEHEADER* r = (BITMAPFILEHEADER*)malloc(bfh->bfSize);
	memcpy(r, bfh, bfh->bfSize);
	return r;
}

BITMAPFILEHEADER* create_24bmp(int w, int h)
{
	//得到每行的字节数
	int rbs = w * 3;
	if (rbs % 4 != 0)
		rbs += 4 - rbs % 4;

	//得到文件总大小
	int all_byte = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + rbs * h;

	//开辟堆内存
	BITMAPFILEHEADER* bfh = (BITMAPFILEHEADER*)malloc(all_byte);

	//填写文件头
	bfh->bfType = 'MB'; //42 4D
    bfh->bfSize = all_byte;
    bfh->bfReserved1 = 0;
    bfh->bfReserved2 = 0;
    bfh->bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

	//填写信息头
	BITMAPINFOHEADER* bih = (BITMAPINFOHEADER*)(bfh + 1);
	bih->biSize = sizeof(BITMAPINFOHEADER);
    bih->biWidth = w;
    bih->biHeight = h;
    bih->biPlanes = 1;
    bih->biBitCount = 24;
    bih->biCompression = 0;
    bih->biSizeImage = 0;
    bih->biXPelsPerMeter = 0;
    bih->biYPelsPerMeter = 0;
    bih->biClrUsed = 0;
    bih->biClrImportant = 0;

	return bfh;
}

void wh_24bmp(BITMAPFILEHEADER* bfh, int* w, int* h)
{
	BITMAPINFOHEADER* bih = (BITMAPINFOHEADER*)(bfh + 1);
	*w = bih->biWidth;
	*h = bih->biHeight;
}

BGR* color_24bmp(BITMAPFILEHEADER* bfh, int x, int y)
{
	//得到每行的字节数
	BITMAPINFOHEADER* bih = (BITMAPINFOHEADER*)(bfh + 1);
	int rbs = bih->biWidth * 3;
	if (rbs % 4 != 0)
		rbs += 4 - rbs % 4;

	//得到颜色并返回
	char* color = (char*)bfh + bfh->bfOffBits;
	return (BGR*)(color + (bih->biHeight - y - 1) * rbs + x * 3);
}

void save_24bmp(BITMAPFILEHEADER* bfh, const char* bmp)
{
	FILE* pf = 0;
	fopen_s(&pf, bmp, "wb");
	fwrite(bfh, 1, bfh->bfSize, pf);
	fclose(pf);
}