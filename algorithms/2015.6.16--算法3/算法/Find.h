#ifndef _FIND_H_
#define _FIND_H_

//如果找到了就返回找到的数据的下标，找不到就返回b-1
template <typename T>
int find_half(const T* p, //待查找的数组
			  int b, //起始位置
			  int e, //终止位置
			  T data, //要查找的数据
			  bool increase = true) //数组排列方式，为真表示升序排列，为假表示降序排列
{
	int r = b - 1;
	if (increase)
	{
		while (b <= e)
		{
			int h = (b + e) / 2;
			if (data < p[h])
				e = h - 1;
			else if (p[h] < data)
				b = h + 1;
			else
				return h;
		}
	}
	else
	{
		while (b <= e)
		{
			int h = (b + e) / 2;
			if (data < p[h])
				b = h + 1;
			else if (p[h] < data)
				e = h - 1;
			else
				return h;
		}
	}
	return r;
}

//顺序集合
//顺序映射
//哈希表
//搜索树
//AVL树
//红黑树
//上面的6种数据结构主要操作都是查找

inline const char* FindStrInStr(const char* s1, const char* s2)
{
	int len1 = 0, len2 = 0;
	for (; s1[len1]; ++len1)
		;
	for (; s2[len2]; ++len2)
		;
	int num = len1 - len2 + 1; //得到字符串总共的比较次数
	for (int i = 0; i < num; ++i)
	{
		bool equal = true;
		for (int j = 0; j < len2; ++j)
		{
			if (s1[i + j] != s2[j])
			{
				equal = false;
				break;
			}
		}
		if (equal)
			return s1 + i;
	}
	return 0;
}

#endif