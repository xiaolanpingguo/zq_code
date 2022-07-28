#ifndef _SORT_H_
#define _SORT_H_

template <typename T>
void sort_bubble(T* p, int b, int e)
{
	//for (int j = 0; j < 4; ++j)
	//{
	//	if (p[j + 1] < p[j])
	//	{
	//		T t = p[j];
	//		p[j] = p[j + 1];
	//		p[j + 1] = t;
	//	}
	//}
	//for (int j = 0; j < 3; ++j)
	//{
	//	if (p[j + 1] < p[j])
	//	{
	//		T t = p[j];
	//		p[j] = p[j + 1];
	//		p[j + 1] = t;
	//	}
	//}
	//for (int j = 0; j < 2; ++j)
	//{
	//	if (p[j + 1] < p[j])
	//	{
	//		T t = p[j];
	//		p[j] = p[j + 1];
	//		p[j + 1] = t;
	//	}
	//}
	//for (int j = 0; j < 1; ++j)
	//{
	//	if (p[j + 1] < p[j])
	//	{
	//		T t = p[j];
	//		p[j] = p[j + 1];
	//		p[j + 1] = t;
	//	}
	//}

	//上面的多个相同代码段可以用一个循环来包含
	//for (int i = 4; i > 0; --i)
	//{
	//	for (int j = 0; j < i; ++j)
	//	{
	//		if (p[j + 1] < p[j])
	//		{
	//			T t = p[j];
	//			p[j] = p[j + 1];
	//			p[j + 1] = t;
	//		}
	//	}
	//}

	//冒泡排序
	p += b; //让p指向要开始排序的位置
	for (int i = e - b; i > 0; --i)
	{
		for (int j = 0; j < i; ++j)
		{
			if (p[j + 1] < p[j])
			{
				T t = p[j];
				p[j] = p[j + 1];
				p[j + 1] = t;
			}
		}
	}
}

template <typename T>
void sort_select(T* p, int b, int e)
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
	
	//上面的多个相同代码段可以用一个循环来包含
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

	p += b;
	int num = e - b;
	for (int i = 0; i < num; ++i)
	{
		int j = i;
		for (int k = j + 1; k < num + 1; ++k)
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


template <typename T>
void sort_quick(T* p, int b, int e)
{
	if (b < e)
	{
		//index就是依次放入比p[b]小的数据的下标
		int index = b;
		for (int i = b + 1; i <= e; ++i)
		{
			if (p[i] < p[b])
			{
				index += 1;
				if (index != i)
				{
					T t = p[i];
					p[i] = p[index];
					p[index] = t;
				}
			}
		}
		if (index != b)
		{
			T t = p[b];
			p[b] = p[index];
			p[index] = t;
		}

		sort_quick(p, b, index - 1);
		sort_quick(p, index + 1, e);
	}
}

template <typename T>
void sort_merge(T* p, int b, int e, T* h)
{
	if (b < e)
	{
		int half = (b + e) / 2;
		sort_merge(p, b, half, h);
		sort_merge(p, half + 1, e, h);

		int i1 = b, i2 = half + 1, i3 = b;

		while (i1 <= half && i2 <= e)
		{
			if (p[i1] < p[i2])
				h[i3++] = p[i1++];
			else
				h[i3++] = p[i2++];
		}
		while (i1 <= half)
			h[i3++] = p[i1++];
		while (i2 <= e)
			h[i3++] = p[i2++];

		//将辅助数组的数据传回给原数组
		for (int i = b; i <= e; ++i)
			p[i] = h[i];
	}
}

#endif