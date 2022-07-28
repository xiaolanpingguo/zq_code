#include<iostream>

//#define A 100
//
//#define ADD(x,y)  (x) + (y);
//
//#define _MAP_W_ 10
//#define _XY(x,y) (x)+(y) * _MAP_W_
//
//#define B

//带参宏分多行完成
//01)最后一行不用写\
//02)不能有注释

#define _MATRIX_MUL(m1,m2,m3,x,y,z)\
for(int i = 0; i < (x); ++i)\
{\
	for(int j = 0; j < (z); ++j)\
	{\
		m3[i][j] = 0;\
		for(int k = 0; k < (y); ++k)\
		{\
			m3[i][j] += m1[i][k] * m2[k][j];\
		}\
	}\
}

void main()
{
	//01
	//int a[6];
	//int b[2][3];
	//for(int i = 0; i < 6; ++i)
	//{
	//	std::cin>>a[i];
	//}

	//for(int i = 0; i < 6; ++i)
	//{
	//	b[i / 3][ i % 3] = a[i];
	//}

	//int a = A;
	//int b = ADD(a,2);

	//2
	int m1[2][3];
	int m2[3][2];
	int m3[2][2];

	for(int i = 0; i < 2; ++i)
	{
		for(int j = 0; j < 3; ++j)
		{
			std::cin>>m1[i][j];
		}
	}

	for(int i = 0; i < 3; ++i)
	{
		for(int j = 0; j < 2; ++j)
		{
			std::cin>>m2[i][j];
		}
	}

	//for(int i = 0; i < 2; ++i)
	//{
	//	for(int j = 0; j < 2; ++j)
	//	{
	//		m3[i][j] = 0;
	//		for(int k = 0; k < 3; ++k)
	//		{
	//			m3[i][j] += m1[i][k] * m2[k][j];
	//		}
	//	}
	//}

	_MATRIX_MUL(m1,m2,m3,2,3,2);
	system("pause");
}