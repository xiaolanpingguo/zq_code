#include <iostream>
#include <windows.h>


void main()
{
	char a[78];
	FILE* pf = 0;
	fopen_s(&pf,"1.bmp","rb");
	fread(a,1,78,pf);
	fclose(pf);

	BITMAPFILEHEADER* p1 = (BITMAPFILEHEADER*)a;
	std::cout<<p1->bfSize<<std::endl;
	//std::cout<<p1->bfType<<std::endl;

	BITMAPINFOHEADER* p2 = (BITMAPINFOHEADER*)(a + 14);
	BITMAPINFOHEADER* p3 = (BITMAPINFOHEADER*)(p1 + 1);
	std::cout<<p2->biWidth<<std::endl;
	std::cout<<p3->biHeight<<std::endl;
	
	system("pause");
}