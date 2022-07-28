#include<iostream>


//void* malloc(size_t size)
//void free(void* memblock)

//在堆内存中分配num * size个字节的连续的内存块
//并返回首地址
//void* calloc(size_t num,size_t size);

//void* f1(size_t num,size_t size)
//{
//	return malloc(num * size);
//}
//先释放memblock所指向的堆内存块，然后在在堆内存块
//中开辟size个字节的连续内存块并返回首地址，新分配
//的内存块和之前释放的内存块没有任何关系
//void* realloc(void* memblock,size_t size);
//void* f2(void* memblock,size_t size)
//{
//	free(memblock);
//	return malloc(size);
//}

int* a;
int d;

void main()
{
	int b;
	a = &b;//用静态内存区中的指针指向main栈
	int* c = &d;//main栈的指针指向静态内存
	int* e = (int*)malloc(4);//main栈中的指针指向堆
	free(e);
	//e = (int*)calloc(sizeof(int),4);
	//free(e);
	//e = (int*)realloc(e,sizeof(int) * 4);
	//free(e);
	int** f = (int**)malloc(4);
	*f = &b;//堆中的指针指向main栈
	free(f);

	system("pause");
}