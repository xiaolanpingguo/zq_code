#include<iostream>
#include "Test.h"

int size = 0;
int length = 0;
char* address = 0;

void Init()
{
	//初始堆内存大小
	size = 8;
	//增长的内存大小
	length = 0;
	//开辟初始大小空间的堆
	address = (char*)malloc(size);
}

void End()
{
	//释放堆内存
	if(address)
		free(address);
}

void Add(void* p ,int c)
{
	//当前堆空间不够，扩展空间
	if(size - length < c)
	{
		//开辟以前两倍大小的堆
		size += c;
		size *= 2; 
		//用新的指针开辟堆
		char* q = (char*)malloc(size);
		//把旧堆的内存拷贝length个大小到新堆
		memcpy(q,address,length);
		//释放旧堆
		free(address);
		//用新指针赋值旧指针
		address = q;
	}
	//拷贝C个字节到旧堆
	memcpy(address + length,p,c);
	//总大小增加C个
	length+=c;
}