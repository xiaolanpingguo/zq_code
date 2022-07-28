#include <iostream>

//void sort_int(int* p, int n)
//{
//	for (int i = n - 1; i > 0; --i)
//	{
//		for (int j = 0; j < i; ++j)
//		{
//			if (p[j] > p[j + 1])
//			{
//				int t = p[j];
//				p[j] = p[j + 1];
//				p[j + 1] = t;
//			}
//		}
//	}
//}
//
//void sort_double(double* p, int n)
//{
//	for (int i = n - 1; i > 0; --i)
//	{
//		for (int j = 0; j < i; ++j)
//		{
//			if (p[j] > p[j + 1])
//			{
//				double t = p[j];
//				p[j] = p[j + 1];
//				p[j + 1] = t;
//			}
//		}
//	}
//}

#include "sort_type.h"

void main()
{
	int a[5] = {};
	double b[5] = {};

	sort_bubble_int(a, 5);
	sort_bubble_double(b, 5);

	system("pause");
}