#include<iostream>

//01)字符串
//size_t就是unsigned int 
//微软认为C语言中一些库函数不安全，所以微软提供
//了一些这些函数的替代版本，用_s作为标记
void main()
{
	//01)
	//返回str代表的字符串的长度，不含结束符
	//size_t strlen(const char* str);

	//std::cout<<strlen("123abc你好")<<std::endl;
	//char* s1 = "xyzdef";
	//std::cout<<strlen(s1)<<std::endl;
	//std::cout<<strlen(s1 + 2)<<std::endl;
	//char s2[] = "9876543210";
	//std::cout<<strlen(&s2[4])<<std::endl;
	//char s3 = 'Z';
	//std::cout<<strlen(&s3)<<std::endl;
	
	//02)
	//将strSource代表的字符串拷贝给strDestination所
	//指向的内存中，包括结束符0一起拷贝，返回strDestination
	//char* strcpy(char* strDestination,const char* strSource);

	//char s4[32] = "abcdefghi";
	//strcpy(s4,"xyz");
	//char s5[] = "ABC";
	//strcpy(s5,"XXYYZZ");//s5没有足够的空间容纳"XXYYZZ"
	//strcpy_s//安全版本

	//03
	//将strSource代表的字符串连接到strDestination
	//所代表的字符串后面，其中sizelnBytes必须填写
	//strDestination所指向的内存上可用的字节数
	//errno_t strcat_s(char* strDestination,
	//	             size_t sizelnBytes,
	//				 const char* strSource);

	//char s7[16] = {};
	//strcat_s(s7,16,"abc");
	//std::cout<<s7<<std::endl;
	//strcat_s(s7,16,"XYZ");
	//std::cout<<s7<<std::endl;
	//strcat_s(s7,16,"QWE");
	//std::cout<<s7<<std::endl;
	//strcat_s(s7,16,"0123456789987");//超出可用字节数
	//std::cout<<s7<<std::endl;

	//04)

	//比较string1,string2两个字符串
	//若string1 > string2返回1
	//若string1 == string2返回0
	//若string1 < string2返回-1
	//int strcmp(const char* string1,const char* string2);
	//std::cout<<strcmp("abc","as")<<std::endl;
	//std::cout<<strcmp("abc","abc")<<std::endl;
	//std::cout<<strcmp("abc","ab")<<std::endl;
	
	//05)
	//返回c在str中第一次出现的地址，没有就返回0
	//char* strchr(const char* str,int c);
	
	std::cout<<strchr("123abc123abc",'a')<<std::endl;
	std::cout<<strchr("123abc123abc",'c') + 4<<std::endl;
	//返回的类型是char*，那么cout就把它当做字符串的首地址
	//打印字符串.0x00000000这个地址是不可访问的

	//std::cout<<strchr("123abc123abc",'x')<<std::endl;
	//读取位置 0x00000000 时发生访问冲突

	//06)
	//返回strSearch再str中第一次出现的地址，没有就返回0
	//char* strstr(const char* str,const char* strSearch);
	
	//std::cout<<strstr("123abc123abc","bc12")+4<<std::endl;
	//const char* s8 = strstr("123abc123abc","bc3");
	//std::cout<<s8<<std::endl;
	system("pause");
}