#include<iostream>
//15)交换两个字符串内容的函数
void stringJiaohuan(char* s1,char* s2)
{
	int len1 = 0;
	while(s1[len1])
		len1++;
	int len2 = 0;
	while(s2[len2])
		len2++;
	int num = len1 > len2 ? len1:len2;
	for(int i = 0; i < num;++i)
	{
		char s = s1[i];
		s1[i] = s2[i];
		s2[i] = s;
	}
}

void stringJiaohuan1(char* s1,char* s2)
{
	int i = 0;
	while(s1[i]||s2[i])
	{
		char s = s1[i];
		s1[i] = s2[i];
		s2[i] = s;
		++i;
	}
	int j = i;
	if(s1[i])
	{
		for(;s2[i] = s1[i];++i)
			;
		s1[j] = 0; 
	}
	if(s2[i])
	{
		for(;s1[i] = s2[i];++i)
			;
		s2[j] = 0; 
	}
}

//16)得到字符在字符串中第一次出现地址的函数
const char* GetDiZhi(const char* s,char c)
{
	const char* p = 0;
	for(int i = 0; s[i];++i)
	{
		if(s[i] == c)
		{
			p = s + i;
			break;
		}
	}
	return p;
}
//17)得到字符在字符串中最后第一次出现地址的函数
const char* GetDiZhiLast(const char* s,char c)
{
	const char* p = 0;
	//for(int i = 0; s[i];++i)
	//{
	//	if(s[i] == c)
	//	{
	//		p = s + i;
	//	}
	//}
	
	int  len = 0;
	while(s[len])
		len++;
	for(int i = len - 1; i >= 0;--i)
	{
		if(s[i] == c)
		{
			p = s + i;
			break;
		}
	}
	return p;
}

int MyStrLen(const char* s)
{
	int  len = 0;
	while(s[len])
		len++;
	return len;
}

//18)得到一个字符串在另一个字符串中第一次出现地址的函数

const char* GetStringDiZhi(const char* s1,const char* s2)
{
	int len1 = MyStrLen(s1);
	int len2 = MyStrLen(s2);
	int num = len1 - len2 + 1;
	for(int i = 0; i < num;++i)
	{
		bool bz = true;
		for(int j = 0; j < len2;++j)
		{
			if(s1[i + j] != s2[j])
			{
				bz = false;
				break;
			}
		}
		if(bz)
			return s1 + i;
	}
	return 0;
}

//19)得到一个字符串在另一个字符串中最后第一次出现地址的函数
const char* GetStringDiZhiLast(const char* s1,const char* s2)
{
	int len1 = MyStrLen(s1);
	int len2 = MyStrLen(s2);
	int num = len1 - len2 + 1;
	const char* p = 0;
	//for(int i = 0; i < num;++i)
	//{
	//	bool bz = true;
	//	for(int j = 0; j < len2;++j)
	//	{
	//		if(s1[i + j] != s2[j])
	//		{
	//			bz = false;
	//			break;
	//		}
	//	}
	//	if(bz)
	//		p = s1 + i;
	//}
	//return p;
	for(int i = len1 - len2; i >= 0;--i)
	{
		bool bz = true;
		for(int j = 0; j < len2;++j)
		{
			if(s1[i + j] != s2[j])
			{
				bz = false;
				break;
			}
		}
		if(bz)
			return s1 + i;
	}
	return 0;
}
//20)得到一个整数的对应字符串的函数
char* GetStrFromInt(int a,char* s)
{
	bool zs = true;
	if(a == 0)
	{
		s[0] = '0';
		s[1] = 0;//'\0'
		return s;
	}
	else if(a < 0)
	{
		a = -a;
		s[0] = '-';
		s+=1;
		zs = false;
	}
	
	int j = 0;
	while(a)
	{
		s[j] = a % 10 + '0';
		a /= 10;
		j++;
	}
	s[j] = 0;
	for(int i = 0; i < j / 2;++i)
	{
		char c = s[i];
		s[i] = s[j - i - 1];
		s[j - i - 1] = c;
	}
	return zs ? s : s - 1;
}

//21)得到一个字符串的对应整数的函数
//	bool Str2Int(const char* s, int* i);
bool Str2Int(const char* s, int* i)
{
	if(s[0] != '+' && s[0] != '-' && (s[0] < '0'|| s[0] > '9'))
		return false;
	for(int j = 1;s[j];++j)
	{
		if(s[j] < '0'|| s[j] > '9')
			return false;
	}
	bool zs = true;
	if(s[0] == '+')
		s += 1;
	else if(s[0] == '-')
	{
		s += 1;
		zs = false;
	}
	*i = 0;
	for(int j = 0; s[j];++j)
	{
		*i = (*i * 10) + (s[j] - '0');
	}
	if(!zs)
		*i = -(*i);
	return true;
}

//22)对内存进行拷贝的函数
//	void* MemoryCopy(void* p1, const void* p2, int num);
//	从p2开始拷贝num个字节到p1所指向的内存区中,并返回p1
void* MemoryCopy(void* p1, const void* p2, int num)
{
	for(int i = 0; i < num;++i)
		((char*)p1)[i] = ((char*)p2)[i];
	return p1;
}

//23)对指定位进行设置的函数
//	void SetBit(void* p, int n, bool b);
//	将p开始的地址上的第n个位设置为(b为true)1或(b为false)0
void SetBit(void* p, int n, bool b)
{
	char* q = (char*)p + n/8;
	// 00100000
	// 00001010
	// 00101010
	if(b)
		*q |= (1<<(7 - n % 8));
	else
		*q &= ~(1<<(7 - n % 8));
}
void main()
{
	char s[256] = "qwert";
	char s1[256] = "zxcv";
	stringJiaohuan1(s,s1);
	std::cout<<(void*)GetDiZhi("assdfg",'a')<<std::endl;
	std::cout<<(void*)GetStringDiZhi("assdfg","sd")<<std::endl;
	
	GetStrFromInt(-123,s);
	
	int i;
	bool a = Str2Int(s,&i);
	char s2[4];//?? ?? ?? ??
	int  b = 49;//31 00 00 00
	MemoryCopy(s2,&b,5);
	int a1 = 0;
	SetBit(&a1,10,1);
	system("pause");
}