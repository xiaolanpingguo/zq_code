#include<iostream>

//02)字符串与其他类型的转换
void main()
{
	//01)
	//将字符串转化为整数并返回，转化不了就返回0
	//int atoi(const char* str);

	int a1 = atoi("123");
	int a2 = atoi("+123");
	std::cout<<a2<<std::endl;
	int a3 = atoi("-123");
	std::cout<<a3<<std::endl;
	int a4 = atoi("abc");
	std::cout<<a4<<std::endl;

	//02)
	//将value转化为字符串并存放到长度为
	//sizelnCharacters的buffer地址中，radix
	//表示进制
	//errno_t_itoa_s(int value,
	//	           char* buffer,
	//			   size_t sizelnCharacters,
	//			   int radix);

	char s1[32];
	_itoa_s(123,s1,32,10);
	std::cout<<s1<<std::endl;

	//printf("hello world\n");
	//printf的作用:格式化字符串并打印
	//"%d"会被整数替换
	//"%f"会被浮点数替换
	//"%c"会被字符替换
	//"%s"会被字符串替换
	//"%p"会被地址替换
	//printf("我要打印的整数是%d+%d=%d\n",100,200,300);
	//printf("%d,%f,%c,%s,%p\n",1,3.14,'A',"abc",&a1);

	//03)
	//格式化字符串并存入字符数组
	//int sprintf_s(char* buffer,
	//	          size_t sizeOfBuffer,
	//			  const char* format,
	//			  ....);

	char s2[64];
	sprintf_s(s2,64,"%d、%f、%c、%s、%p\n",1,3.14,'A',"abc",&a1);
	std::cout<<s2<<std::endl;
	system("pause");
}