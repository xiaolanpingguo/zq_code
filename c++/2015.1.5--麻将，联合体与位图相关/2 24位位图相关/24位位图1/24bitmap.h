#ifndef _24_BITMAP_H_
#define _24_BITMAP_H_

#include <iostream>
#include <windows.h>

//打开24位位图文件
BITMAPFILEHEADER* Open_24bmp(const char* fn);

//拷贝24位位图文件
BITMAPFILEHEADER* Copy_24bmp(BITMAPFILEHEADER* pbfh);

//保存24位位图文件
void Save_24bmp(const char* fn, BITMAPFILEHEADER* pbfh);

//关闭24位位图文件
void Close_24bmp(BITMAPFILEHEADER* pbfh);

//得到位图宽、高
void WH_24bmp(BITMAPFILEHEADER* pbfh, int* w, int* h);

//颜色结构体
struct _YS
{
	unsigned char b, g, r;
};
//得到指定位置的颜色
_YS* color_24bmp(BITMAPFILEHEADER* pbfh, int x, int y);

#endif