#include "24bitmap.h"

BITMAPFILEHEADER* Open_24bmp(const char* fn)
{
	FILE* pf = 0;
	fopen_s(&pf, fn, "rb");
	if (!pf)
		return 0;

	fseek(pf, 0, SEEK_END);
	int fs = ftell(pf);
	rewind(pf);
	BITMAPFILEHEADER* pbfh = (BITMAPFILEHEADER*)malloc(fs);
	fread(pbfh, 1, fs, pf);
	fclose(pf);

	return pbfh;
}

//拷贝24位位图文件
BITMAPFILEHEADER* Copy_24bmp(BITMAPFILEHEADER* pbfh)
{
	BITMAPFILEHEADER* q = (BITMAPFILEHEADER*)malloc(pbfh->bfSize);
	memcpy(q, pbfh, pbfh->bfSize);
	return q;
}

BITMAPFILEHEADER* Create_24bmp(int w, int h)
{
	//得到每行所占字节数
	int rowbytes = w * 3;
	if (rowbytes % 4 != 0)
		rowbytes += 4 - rowbytes % 4;

	//得到文件总大小
	int filesize = 54 + rowbytes * h;

	//开辟内存空间
	BITMAPFILEHEADER* pbfh = (BITMAPFILEHEADER*)malloc(filesize);

	//填写文件头数据
	pbfh->bfType = 'MB';
	pbfh->bfSize = filesize;
	pbfh->bfReserved1 = 0;
	pbfh->bfReserved2 = 0;
	pbfh->bfOffBits = 54;

	//填写信息头数据
	BITMAPINFOHEADER* pbih = (BITMAPINFOHEADER*)(pbfh + 1);
	pbih->biSize = 40;
	pbih->biWidth = w;
	pbih->biHeight = h;
	pbih->biPlanes = 1;
	pbih->biBitCount = 24;
	pbih->biCompression = 0;
	pbih->biSizeImage = 0;
	pbih->biXPelsPerMeter = 0;
	pbih->biYPelsPerMeter = 0;
	pbih->biClrUsed = 0;
	pbih->biClrImportant = 0;

	return pbfh;
}

//保存24位位图文件
void Save_24bmp(const char* fn, BITMAPFILEHEADER* pbfh)
{
	FILE* pf = 0;
	fopen_s(&pf, fn, "wb");
	fwrite(pbfh, 1, pbfh->bfSize, pf);
	fclose(pf);
}

//关闭24位位图文件
void Close_24bmp(BITMAPFILEHEADER* pbfh)
{
	free(pbfh);
}

//得到位图宽、高
void WH_24bmp(BITMAPFILEHEADER* pbfh, int* w, int* h)
{
	BITMAPINFOHEADER* pbih = (BITMAPINFOHEADER*)(pbfh + 1);
	*w = pbih->biWidth;
	*h = pbih->biHeight;
}

//得到指定位置的颜色
_YS* color_24bmp(BITMAPFILEHEADER* pbfh, int x, int y)
{
	_YS* p = (_YS*)((char*)pbfh + 54);

	//得到一行有多少字节
	BITMAPINFOHEADER* pbih = (BITMAPINFOHEADER*)(pbfh + 1);
	int rowbytes = pbih->biWidth * 3;
	if (rowbytes % 4 != 0)
		rowbytes += 4 - rowbytes % 4;

	return (_YS*)((char*)p + (pbih->biHeight - 1 - y) * rowbytes + 3 * x);
}

