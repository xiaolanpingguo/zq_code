#include<iostream>

//在堆内存中开辟size个字节的连续的内存块并
//返回其首地址
//void* malloc(size_t size);
//释放memblock所指向的堆内存块
//void free(void* memblock);

void main()
{
	int a = sizeof(int) * 5;
	//在堆内存中开辟了20个字节的连续的内存块
	//并将该内存块的首地址初始化给int类型的指针p
	int* p = (int*)malloc(a);//实参可以是任意的表达式
	
	//int c[a];
	//栈，静态内存区中的数组在定义的时候必须是结果为
	//大于0的int类型的常量表达式
	
	//堆内存的使用和其他内存的使用是没有区别的
	//任何内存区的使用都不能越界
	for(int i = 0; i < 5;++i)
		p[i] = i + 10;
	for(int i = 0; i < 5;++i)
		std::cout<<p[i]<<std::endl;
	
	//p[5] = 1;

	//所谓的释放堆内存，就是标记该内存块不能再
	//使用，即本程序放弃该内存块的使用权，也可
	//理解为把该内存块还给操作系统
	//free(p);

	//free()中填写的实参必须是堆内存的首地址
	//free(p + 1);
	//free()中只要填写的表达式是堆内存的首地址即可
	//无论是什么样的表达式以及什么类型的地址

	short* q = (short*)p;
	free(q + 1 - 1);
	//p[0] = 1;

	//free(p);//针对同一堆内存的释放只能有一次
	
	//p作为一个指针可以继续使用
	int b;
	p = &b;
	//堆内存如果不释放就一直存在，当我们不使用个某
	//块堆内存的时候就必须手动调用free去释放它，
	//保证我们的程序中没有内存泄露(有内存忘记释放)
	//如果一块堆内存分配出来没有释放之前，在调用malloc
	//是绝不会再分配到它的.
	system("pause");
}