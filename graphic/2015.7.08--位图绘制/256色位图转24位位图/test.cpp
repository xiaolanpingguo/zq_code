#include <iostream>
#include <windows.h>

struct _BGR
{
	unsigned char b, g, r;
};

void main()
{
	//'ab'在内存中占2个字节分别是：62 61
	short x = 'ab';

	std::cout<<"请输入256色位图文件路径：";
	char fn[256];
	std::cin>>fn;

	//得到位图文件头
	FILE* pf = 0;
	fopen_s(&pf, fn, "rb");
	if (!pf)
	{
		std::cout<<"无法打开指定文件！";
		system("pause");
		return;
	}
	fseek(pf, 0, SEEK_END);
	int fs = ftell(pf);
	rewind(pf);
	BITMAPFILEHEADER* bfh = (BITMAPFILEHEADER*)malloc(fs);
	fread(bfh, 1, fs, pf);
	fclose(pf);

	//得到信息头
	BITMAPINFOHEADER* bih = (BITMAPINFOHEADER*)(bfh + 1);
	if (bih->biBitCount != 8)
	{
		std::cout<<"打开的不是256色位图！";
		system("pause");
		free(bfh);
		return;
	}

	//得到颜色表
	int* color_table = (int*)(bih + 1);

	//得到颜色
	unsigned char* color = (unsigned char*)bfh + bfh->bfOffBits;

	//得到每行字节数
	int rbs8 = bih->biWidth;
	if (rbs8 % 4 != 0)
		rbs8 += 4 - rbs8 % 4;

	//得到24位位图所需字节数
	int rbs24 = bih->biWidth * 3;
	if (rbs24 % 4 != 0)
		rbs24 += 4 - rbs24 % 4;
	int all_bytes = 54 + rbs24 * bih->biHeight;

	//填写24位位图的文件头
	BITMAPFILEHEADER bfh24
		=
	{
		'MB', //BM
		all_bytes,
		0,
		0,
		54
	};

	//填写24位位图的信息头
	BITMAPINFOHEADER bih24
		=
	{
		40,
		bih->biWidth,
		bih->biHeight,
		1,
		24
	};

	//填写24位位图的颜色数据
	char* color24 = (char*)malloc(all_bytes - 54);
	for (int y = 0; y < bih->biHeight; ++y)
	{
		for (int x = 0; x < bih->biWidth; ++x)
		{
			//得到颜色
			int i = *(color + (bih->biHeight - y - 1) * rbs8 + x);
			_BGR* p = (_BGR*)(&color_table[i]);
			_BGR* q = (_BGR*)(color24 + (bih->biHeight - y - 1) * rbs24 + x * 3);
			*q = *p;
		}
	}

	//写入文件
	std::cout<<"请输入24位位图文件路径：";
	std::cin>>fn;

	//写入文件
	fopen_s(&pf, fn, "wb");
	fwrite(&bfh24, 1, 14, pf);
	fwrite(&bih24, 1, 40, pf);
	fwrite(color24, 1, all_bytes - 54, pf);
	fclose(pf);

	std::cout<<"转换成功，";
	system("pause");

	free(color24);
	free(bfh);
}