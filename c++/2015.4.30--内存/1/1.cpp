#include <iostream>
#include <windows.h>

//冒泡排序
//选择排序
//折半查找

//折半查找的前提条件是待查找数据的数组已经排好了序
int _1(int* p, int n, int d)
{
	int b = 0, e = n - 1;
	while (b <= e)
	{
		int h = (b + e) / 2;
		if (d < p[h])
			e = h - 1;
		else if (p[h] < d)
			b = h + 1;
		else
			return h;
	}
	return -1;
}

bool _2_1(const short* p1, int n1, const short* p2, int n2)
{
	for (int i = 0; i < n1; ++i)
	{
		for (int j = 0; j < n2; ++j)
		{
			if (p1[i] == p2[j])
				return true;
		}
	}
	return false;
}

//p1[2][1][3][4]
//p2[4][3][7][8][0]
//[false][ true][ true][ true][ true][false][false][false][false]
// 32768  32769  32770  32771  32772  32773  32774  32775  32776
bool _2_2(const short* p1, int n1, const short* p2, int n2)
{
	//定义一个辅助数组全部初始化为false，注意此处是因为
	//short的取值范围是在-32768~32767之间，所以可以使用
	//一个长度为65536的数组来进行标记设置，以加快判断的
	//速度，但是int之类的不能这么做
	bool help[65536] = {};
	for (int i = 0; i < n1; ++i)
		help[p1[i] + 32768] = true; //-32768~32767 -> 0~65535
	for (int i = 0; i < n2; ++i)
	{
		if (help[p2[i] + 32768])
			return true;
	}
	return false;
}

int _3_1(unsigned char c)
{
	int num = 0;
	while (c)
	{
		if (c % 2 == 1)
			num += 1;
		c /= 2;
	}
	return num;
}

int _3_2(unsigned char c)
{
	int num = 0;
	while (c)
	{
		if (c & 1)
			num += 1;
		c >>= 1;
	}
	return num;
}

int init_help(int* help)
{
	for (int i = 0; i < 256; ++i)
		help[i] = _3_2(i);
	return 1;
}
int _3_3(unsigned char c)
{
	//x是静态局部变量，其定义（含初始化）语句只
	//在最初调用本函数的时候执行1次
	static int help[256];
	static int x = init_help(help);
	return help[c];
}

int _3_4(int i)
{
	//x是静态局部变量，其定义（含初始化）语句只
	//在最初调用本函数的时候执行1次
	static int help[256];
	static int x = init_help(help);
	unsigned char* p = (unsigned char*)&i;
	return help[p[0]] + help[p[1]] + help[p[2]] + help[p[3]];
}

char* _4(char* s1, char* s2)
{
	int i1 = 0, i2 = 0;
	while (s1[i1])
		i1++;
	while (s2[i2])
		i2++;
	int i3 = i1 - i2 + 1;
	for (int i = 0; i < i3; ++i)
	{
		bool ok = true;
		for (int j = 0; j < i2; ++j)
		{
			if (s1[i + j] != s2[j])
			{
				ok = false;
				break;
			}
		}
		if (ok)
			return s1 + i;
	}
	return 0;
}

struct NODE
{
	NODE* left;
	NODE* right;
};
int height(NODE* p)
{
	if (p)
	{
		int left_h = height(p->left);
		int right_h = height(p->right);
		return left_h > right_h ? left_h + 1 : right_h + 1;
	}
	else
		return 0;
}

void main()
{
	std::cout<<_3_3(255)<<std::endl;
	std::cout<<_3_3(255)<<std::endl;
	std::cout<<_3_3(255)<<std::endl;
	std::cout<<_3_3(255)<<std::endl;

	char* p = _4("abdefslkdfjjslksdf", "slk");

	NODE n1 = {};
	NODE n2 = {};
	NODE n3 = {};
	NODE n4 = {};
	NODE n5 = {};
	NODE n6 = {};
	NODE n7 = {};
	NODE n8 = {};
	n1.left = &n2;
	n1.right = &n3;
	n2.left = &n4;
	n2.right = &n5;
	n5.left = &n6;
	n6.left = &n7;
	n6.right = &n8;
	std::cout<<height(&n1)<<std::endl;
	std::cout<<height(&n2)<<std::endl;
	std::cout<<height(&n3)<<std::endl;
	
	system("pause");
}

//栈
//静态
//堆
//常量
//指令
