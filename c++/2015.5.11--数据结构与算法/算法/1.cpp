#include <iostream>

template <typename T>
void sort_bubble(T* p, int begin, int end, bool increase = true)
{
	//将指针移动到开始排序的位置
	p += begin;

	//得到总的排序数据的总数
	int num = end - begin + 1;

	if (increase)
	{
		//for (int j = 0; j < 4; ++j)
		//{
		//	if (p[j + 1] < p[j])
		//	{
		//		T t = p[j + 1];
		//		p[j + 1] = p[j];
		//		p[j] = t;
		//	}
		//}
		//for (int j = 0; j < 3; ++j)
		//{
		//	if (p[j + 1] < p[j])
		//	{
		//		T t = p[j + 1];
		//		p[j + 1] = p[j];
		//		p[j] = t;
		//	}
		//}
		//for (int j = 0; j < 2; ++j)
		//{
		//	if (p[j + 1] < p[j])
		//	{
		//		T t = p[j + 1];
		//		p[j + 1] = p[j];
		//		p[j] = t;
		//	}
		//}
		//for (int j = 0; j < 1; ++j)
		//{
		//	if (p[j + 1] < p[j])
		//	{
		//		T t = p[j + 1];
		//		p[j + 1] = p[j];
		//		p[j] = t;
		//	}
		//}

		//for (int i = 4; i > 0; --i)
		//{
		//	for (int j = 0; j < i; ++j)
		//	{
		//		if (p[j + 1] < p[j])
		//		{
		//			T t = p[j + 1];
		//			p[j + 1] = p[j];
		//			p[j] = t;
		//		}
		//	}
		//}

		for (int i = num - 1; i > 0; --i)
		{
			for (int j = 0; j < i; ++j)
			{
				if (p[j + 1] < p[j])
				{
					T t = p[j + 1];
					p[j + 1] = p[j];
					p[j] = t;
				}
			}
		}
	}
	else
	{
		for (int i = num - 1; i > 0; --i)
		{
			for (int j = 0; j < i; ++j)
			{
				if (p[j] < p[j + 1])
				{
					T t = p[j + 1];
					p[j + 1] = p[j];
					p[j] = t;
				}
			}
		}
	}
}

template <typename T>
void sort_select(T* p, int begin, int end, bool increase = true)
{
	//将指针移动到开始排序的位置
	p += begin;

	//得到总的排序数据的总数
	int num = end - begin + 1;

	if (increase)
	{
		//int j = 0;
		//for (int k = j + 1; k < 5; ++k)
		//{
		//	if (p[k] < p[j])
		//		j = k;
		//}
		//if (j != 0)
		//{
		//	T t = p[j];
		//	p[j] = p[0];
		//	p[0] = t;
		//}

		//int j = 1;
		//for (int k = j + 1; k < 5; ++k)
		//{
		//	if (p[k] < p[j])
		//		j = k;
		//}
		//if (j != 1)
		//{
		//	T t = p[j];
		//	p[j] = p[1];
		//	p[1] = t;
		//}

		//int j = 2;
		//for (int k = j + 1; k < 5; ++k)
		//{
		//	if (p[k] < p[j])
		//		j = k;
		//}
		//if (j != 2)
		//{
		//	T t = p[j];
		//	p[j] = p[2];
		//	p[2] = t;
		//}

		//int j = 3;
		//for (int k = j + 1; k < 5; ++k)
		//{
		//	if (p[k] < p[j])
		//		j = k;
		//}
		//if (j != 3)
		//{
		//	T t = p[j];
		//	p[j] = p[3];
		//	p[3] = t;
		//}

		//for (int i = 0; i < 4; ++i)
		//{
		//	int j = i;
		//	for (int k = j + 1; k < 5; ++k)
		//	{
		//		if (p[k] < p[j])
		//			j = k;
		//	}
		//	if (j != i)
		//	{
		//		T t = p[j];
		//		p[j] = p[i];
		//		p[i] = t;
		//	}
		//}

		for (int i = 0; i < num - 1; ++i)
		{
			int j = i;
			for (int k = j + 1; k < num; ++k)
			{
				if (p[k] < p[j])
					j = k;
			}
			if (j != i)
			{
				T t = p[j];
				p[j] = p[i];
				p[i] = t;
			}
		}
	}
	else
	{
		for (int i = 0; i < num - 1; ++i)
		{
			int j = i;
			for (int k = j + 1; k < num; ++k)
			{
				if (p[j] < p[k])
					j = k;
			}
			if (j != i)
			{
				T t = p[j];
				p[j] = p[i];
				p[i] = t;
			}
		}
	}
}

template <typename T>
int half_search(T* p, int begin, int end, T data, bool increase = true)
{
	if (increase)
	{
		while (begin <= end)
		{
			//int half = (begin + end) / 2;
			int half = (begin + end) >> 1;
			if (data < p[half])
				end = half - 1;
			else if (p[half] < data)
				begin = half + 1;
			else
				return half; //!(data < p[half]) && !(p[half] < data)
		}
	}
	else
	{
		while (begin <= end)
		{
			//int half = (begin + end) / 2;
			int half = (begin + end) >> 1;
			if (data < p[half])
				begin = half + 1;
			else if (p[half] < data)
				end = half - 1;
			else
				return half; //!(data < p[half]) && !(p[half] < data)
		}
	}

	return -1;
}

void main()
{
	int a[] = {5, 8, 7, 6, 4};
	sort_select<int>(a, 0, 4, false);
	for (int i = 0; i < 5; ++i)
		std::cout<<half_search(a, 0, 4, a[i], false)<<std::endl;
	std::cout<<half_search(a, 0, 4, 9, false)<<std::endl;

	system("pause");
}