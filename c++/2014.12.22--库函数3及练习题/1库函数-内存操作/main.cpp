#include<iostream>

//内存操作

void main()
{
	//01)

	//将dest开始的地址上面的count个字节赋值为
	//c的第一个字节，返回dest
	//void* memset(void* dest,int c,size_t count);

	char s[100];
	memset(s,0xaabbccdd,100);


	//02)

	//将src开始的地址上面的count个字节赋值到dest地址上面
	//的count个字节中
	//void* memcpy(void* dest,const void* src,size_t count);
	
	int a = 0;
	char b[6] = {1,2,3,4};

	memcpy(&a,b,3);

	std::cout<<a<<std::endl;
	
	system("pause");
}