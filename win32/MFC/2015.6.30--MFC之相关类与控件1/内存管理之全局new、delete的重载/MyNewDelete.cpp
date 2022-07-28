//可以通过重载全局的new、delete、
//new []、delete []个运算符达到
//内存跟踪的目的，通过下面的代码
//我们可以接管原始的堆内存操作，
//一般来说我们可以通过下面的代码
//来记录堆内存的分配、释放情况，
//如果要想跟踪malloc和free，那么
//只能用“钩子”技术来完成

#include <iostream>

int new_num = 0;
int delete_num = 0;

void* operator new (size_t size)
{
	void* mem = malloc(size);

	//记录分配信息
	char buf[256];
	sprintf_s(buf, 256, "分配了%d个字节在地址%p,当前分配%d释放%d\r\n", size, mem, ++new_num, delete_num);
	FILE* pf = 0;
	fopen_s(&pf, "HeapLog.txt", "a"); //wb会清空原文件，a只是打开不会清空
	fwrite(buf, strlen(buf), 1, pf);
	fclose(pf);

	return mem;
}

void operator delete (void* mem)
{
	free(mem);

	//记录释放信息
	char buf[256];
	sprintf_s(buf, 256, "释放了%p,当前分配%d释放%d\r\n", mem, new_num, ++delete_num);
	FILE* pf = 0;
	fopen_s(&pf, "HeapLog.txt", "a");
	fwrite(buf, strlen(buf), 1, pf);
	fclose(pf);
}

void* operator new [] (size_t size)
{
	return operator new (size);
}

void operator delete [] (void* mem)
{
	operator delete (mem);
}