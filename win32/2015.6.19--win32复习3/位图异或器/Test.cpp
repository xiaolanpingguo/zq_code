// Test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>

int _tmain(int argc, _TCHAR* argv[])
{
	char fn[256];
	std::cout<<"请输入要加密的位图：";
	std::cin>>fn;

	FILE* pf = 0;
	fopen_s(&pf, fn, "rb");
	if (!pf)
		return 0;

	fseek(pf, 0, SEEK_END);
	int fs = ftell(pf);
	rewind(pf);

	char* fd = new char[fs];
	fread(fd, 1, fs, pf);
	fclose(pf);

	//异或
	for (int i = 0; i < fs; ++i)
	{
		fd[i] = fd[i] ^ 0xa7;
	}

	std::cout<<"请输入要生成的加密位图：";
	std::cin>>fn;
	fopen_s(&pf, fn, "wb");
	fwrite(fd, 1, fs, pf);
	fclose(pf);

	std::cout<<"生成成功！";

	system("pause");
	return 0;
}

