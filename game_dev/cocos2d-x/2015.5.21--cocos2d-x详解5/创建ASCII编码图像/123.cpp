// 123.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	FILE* pf = 0;
	fopen_s(&pf, "ASCII.txt", "wb");


	//ASCII编码的前0~31个字符是控制字符，是打印
	//不出来的，强行用记事本显示的话就是乱码
	char x = ' ';
	for (int i = 0; i <= 31; ++i)
		fwrite(&x, 1, 1, pf);
	
	//打印32~127的文字
	for (int i = 32; i <= 127; ++i)
	{
		if (i % 32 == 0)
			fwrite("\r\n", 2, 1, pf);
		x = i;
		fwrite(&x, 1, 1, pf);
	}
	fclose(pf);

	return 0;
}

