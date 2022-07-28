// a.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "iostream"

int get_rand_int(int min, int max)
{
	return rand() % (max - min + 1) + min;
}

int _tmain(int argc, _TCHAR* argv[])
{
	int w, h;
	int min, max;

	do
	{
		std::cout<<"请输入要生成的地图宽：";
		std::cin>>w;
		std::cout<<"请输入要生成的地图高：";
		std::cin>>h;
	} while (w < 1 || h < 1);

	do
	{
		std::cout<<"请输入要生成的地图数据小值：";
		std::cin>>min;
		std::cout<<"请输入要生成的地图数据大值：";
		std::cin>>max;
	} while (min < 0 || max < min || max > 9);

	char fn[256];
	std::cout<<"请输入生成的地图文件名：";
	std::cin>>fn;

	std::cout<<"即将生成随机地图，";
	system("pause");
	
	char* p = new char[(w + 2) * h];
	for (int y = 0; y < h; ++y)
	{
		//写入该行数据
		for (int x = 0; x < w; ++x)
			p[y * (w + 2) + x] = get_rand_int(min + '0', max + '0');
		p[y * (w + 2) + w + 0] = '\r';
		p[y * (w + 2) + w + 1] = '\n';
	}

	FILE* pf = 0;
	fopen_s(&pf, fn, "wb");
	fwrite(p, 1, (w + 2) * h, pf);
	fclose(pf);

	return 0;
}

