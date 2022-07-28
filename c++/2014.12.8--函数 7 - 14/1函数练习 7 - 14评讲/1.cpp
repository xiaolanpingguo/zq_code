#include<iostream>

//函数的形式参数在遇到数组时，
//形式参数必须是指针或者地址
//必须通过指针或者是地址的形式传递
//
//在函数中，除非是专门的输入输出函数，其他
//函数严禁出现输入或者输出语言
//
//

//07)得到一个数组中最大的元素和最小的元素的函数(只用调一次就得到最大、最小)
void GetMaxAndMin(const int* p,//传入的数组
				  int n,//数组长度
				  int* max,//返回的最大值
				  int* min)//返回的最小值
{
	*max = *min = p[0];
	for(int i = 1;i < n;++i)
	{
		if(*min > p[i])
			*min = p[i];
		if(*max < p[i])
			*max = p[i];
	}
}
//08)对一个数组的一段进行升序或降序排序的函数
void PaiXu(int* p,//传入的数组
		   int begin,//排序开始位置
		   int end,//排序结束位置
		   bool increase)//选择是升序还是降序为true就是升序
{
	//1
	//for(int i = begin;i < end;++i)
	//{
	//	for(int  j = 0; j <= end - i - 1;++j)
	//	{
	//		if(increase)
	//		{
	//			if(p[begin + j] > p[begin + j + 1])
	//			{
	//				//交换
	//				int temp = p[begin + j];
	//				p[begin + j] = p[begin + j + 1];
	//				p[begin + j + 1] = temp;
	//			}
	//		}
	//		else
	//		{
	//			if(p[begin + j] < p[begin + j + 1])
	//			{
	//				//交换
	//				int temp = p[begin + j];
	//				p[begin + j] = p[begin + j + 1];
	//				p[begin + j + 1] = temp;
	//			}
	//		}
	//	}
	//}
	//2
	p += begin;
	int n = end - begin + 1;
	if(increase)
	{
		//冒泡排序
		for(int i = n - 1; i > 0;--i)
		{
			for(int j = 0; j < i;++j)
			{
				if(p[j] > p[j + 1])
				{
					int temp = p[j];
					p[j] = p[j + 1];
					p[j + 1] = temp;
				}
			}
		}
	}
	else
	{
		//选择排序方式
		for(int i = 0; i < n - 1; ++i)
		{
			int j = i;
			for(int k = j + 1; k < n;++k)
			{
				if(p[j] < p[k])
					j = k;
			}
			if(j != i)
			{
				int temp = p[j];
				p[j] = p[i];
				p[i] = temp;
			}
		}
	}
}

//09)得到字符串长度的函数
int GetStringLen(const char* s)//传入的字符串
{
	int i = 0;
	for(;s[i];++i)//while(s[i])
		;		  //  ++i;
	return i;
}

//10)对字符串进行逆序的函数
void LiXu1(char* s)
{
	int Len = 0;
	for(;s[Len];++Len)
		;	
	int num = Len / 2;//Len >> 1
	for(int i = 0; i < num;++i)
	{
		char x = s[i];
		s[i] = s[Len - i - 1];
		s[Len - i - 1] = x;
	}
}

char* LiXu2(char* s)
{
	int Len = 0;
	for(;s[Len];++Len)
		;	
	int num = Len / 2;//Len >> 1
	for(int i = 0; i < num;++i)
	{
		char x = s[i];
		s[i] = s[Len - i - 1];
		s[Len - i - 1] = x;
	}
	return s;
}

//11)对字符串进行拷贝的函数
char* StringCopy(char* s1,//要拷贝到的字符串
				 const char* s2)//被拷贝的字符串
{
	for(int i = 0;s1[i] = s2[i];++i)
		;
	return s1;
}

//12)对字符串进行连接的函数
char* StringLinJie(char* s1,const char* s2)
{
	char* q = s1;
	for(;*q;++q)
		;
	for(int i = 0; q[i] = s2[i];++i)
		;
	return s1;
}

//13)对字符串进行比较的函数
int StringBijiao(const char* s1,const char* s2)
{
	int i = 0;
	while(s1[i]||s2[i])
	{
		if(s1[i] > s2[i])
			return 1;
		else if(s1[i] < s2[i])
			return -1;
		else 
			++i;
	}
	return 0;
}

//14)对字符串中出现的大写字母小写化或者小写字母大写化的函数
char* ChangeChar(char* s,bool dbx)
{
	for(int i = 0;s[i];++i)
	{
		if(dbx && (s[i] >= 'A'&&s[i]<= 'Z'))
			s[i] += 32;
		else if(!dbx && (s[i] >= 'a'&&s[i]<= 'z'))
			s[i] -= 32;
	}
	return s;
}

//15)交换两个字符串内容的函数

void main()
{
	int a[5] = {2,4,1,6,8};
	int max,min;
	GetMaxAndMin(a,5,&max,&min);
	char s[256] = "123456";
	//LiXu2("abcdef");
	//char* s = "123dg";
	//s指向的是常量内存区的地址
	//"abcdef"是常量内存区的地址，
	//不能进行写操作
	char* s1 = LiXu2(s);
	char s2[256] = "asssss";
	char* s3 = StringCopy(s,s2);

	//char s4[] = "1234ddd";
	//char s5[] = "sss";
	//StringCopy(s5,s4);//s5长度只有4字节.s4有8字节，数组访问越界.
	
	char s4[256] = "1234ddd";
	char s5[] = "sss";
	StringLinJie(s4,s5);
	//字符串连接时，目标字符数组的数组长度
	//必须等于或者大于源字符串(字符数组)的所占字节数
	//加目标字符数组的所占字节数在减1.

	StringBijiao("sds","sdsfsdfsd");

	ChangeChar(s4,false);
	system("pause");
}