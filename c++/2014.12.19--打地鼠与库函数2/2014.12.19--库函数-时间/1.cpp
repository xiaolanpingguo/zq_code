#include<iostream>
#include<time.h>


void main()
{
	//字符串长度，不含结束符
	//size_t strlen(const char* str);

	//字符串拷贝
	//char* strcpy(char* strDestination ,const char* strSource);
	
	//字符串连接
	//errno_t strcat_s(char* strDestination,
	//	             size_t sizelnBytes,
	//				 const char* strSource);

	//字符串比较
	//int strcmp(const char* string1,const char* string2);
	
	//查找字符在字符串中第一次出现的地址
	//char* strchr(const char* str,int c);

	//查找字符串在另一个字符串中第一次出现的地址
	//char* strstr(const char* str,const char* strSearch);
	
	//将字符串转化为整数
	//int atoi(const char* str);

	//将整数转化为字符串
	//errno_t _itoa_s(int value,
	//				char* buffer,
	//				size_t sizelnCharacters,
	//				int radix);

	//格式化字符串并打印
	//printf: %d,%f,%c,%s,%p

	//格式化字符串并存入字符数组
	//int sprintf_s(char* buffer,
	//	          size_t sizeOfBuffer,
	//			  const char* format,
	//			  ....);//数据

	//时间函数
	//time_t 本质就是一个__int64，__int64是微软为
	//C++扩充的8字节大整数
	
	//01)得到格林威治时间（秒）
	//time_t time(time_t* timer);

	//time_t t1 = time(0);
	//time_t t2;
	//time(&t2);


	//02)将指定的格林威治时间转化为标准的日期时间字符串
	//errno_t ctime_s(char* buffer,//存储日期时间字符串的字符数组首地址
	//	            size_t sizelnBytes,//存储日期时间字符串的字符数组长度
	//				const time_t* time);//格林威治时间

	//char t[32];
	//ctime_s(t,32,&t1);
	//std::cout<<t<<std::endl;

	system("pause");
}