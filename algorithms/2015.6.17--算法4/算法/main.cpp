#include <iostream>
#include <windows.h>
#include "FindPath.h"
#include "Compress.h"
#include "Find.h"
#include "Sort.h"

#define _MAX_NUM 100
int a[_MAX_NUM];
int b[_MAX_NUM];

//打印整数的时候
//如果整数是非字符类型的整数，那么就打印数值
//如果整数是字符类型（char、unsigned char、
//wchar_t）的整数，那么就打印该整数对应的文字

//打印地址的时候
//如果地址是非字符类型的地址，那么就打印地址
//如果地址是字符类型（char、unsigned char、
//wchar_t）的地址，那么就将该地址当做一个字符
//串的首地址打印字符串

void main()
{
	for (int i = 0; i < _MAX_NUM; ++i)
		a[i] = rand();

	int t0 = GetTickCount();
	sort_quick<int>(a, 0, _MAX_NUM - 1);
	std::cout<<GetTickCount() - t0<<std::endl;

	int t1 = GetTickCount();
	sort_merge<int>(a, 0, _MAX_NUM - 1, b);
	std::cout<<GetTickCount() - t1<<std::endl;

	int x[] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21};
	int i1 = find_half<int>(x, 0, 10, 15, true);

	int y[] = {20, 18, 16, 14, 10, 8, 6, 4, 2, 0};
	int i2 = find_half<int>(y, 0, 9, 19, false);

	const char* s1 = "123abc456defabc123abcxyz";
	const char* s2 = "abc";

	//将所有出现了abc的地址都打印出来
	const char* s3 = s1;
	while (s3)
	{
		s3 = FindStrInStr(s3, s2);
		if (s3)
		{
			std::cout<<"0x"<<(void*)s3<<std::endl;
			s3 += strlen(s2);
		}
	}

	unsigned char buf[]
	=
	{
		0xaa, 0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xab,0xab,0xab,0xab,0xac,0xad
	};

	int len2;
	RLE_Compress(buf, 14, 0, &len2);

	void* buf2 = malloc(len2);
	RLE_Compress(buf, 14, buf2, &len2);
	//aa aa 20 ab ab 10 ac ad

	system("pause");
}