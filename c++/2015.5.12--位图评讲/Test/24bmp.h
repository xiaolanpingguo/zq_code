#ifndef _24_BMP_H_
#define _24_BMP_H_

#include <windows.h>

BITMAPFILEHEADER* open_24bmp(const char* bmp);
BITMAPFILEHEADER* copy_24bmp(BITMAPFILEHEADER* bfh);
BITMAPFILEHEADER* create_24bmp(int w, int h);
void wh_24bmp(BITMAPFILEHEADER* bfh, int* w, int* h);
struct BGR
{
	unsigned char b, g, r;
};
BGR* color_24bmp(BITMAPFILEHEADER* bfh, int x, int y);
void save_24bmp(BITMAPFILEHEADER* bfh, const char* bmp);

#endif