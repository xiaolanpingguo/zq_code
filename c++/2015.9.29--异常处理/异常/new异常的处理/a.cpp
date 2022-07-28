#include <iostream>

//有些服务器程序为了避免真的出现内存耗尽，它会在一开始
//先分配一些内存，当出现内存耗尽的时候，它就是释放一些
//内存

#define _MEM_NUM 10

void my_main()
{
	//...
}

void main()
{
	//提前分配了40MB内存以备后面出现内存告急的时候使用
	void* p[_MEM_NUM];
	for (int i = 0; i < _MEM_NUM; ++i)
		p[i] = malloc(1024 * 1024 * 4);

	int index = 0;
	while (index < 10)
	{
		try
		{
			my_main();
		}
		catch (std::bad_alloc)
		{
			//出现了std::bad_alloc表明当前内存消
			//耗完毕，本程序就释放4MB内存
			free(p[index++]);
		}
	}

	system("pause");
}