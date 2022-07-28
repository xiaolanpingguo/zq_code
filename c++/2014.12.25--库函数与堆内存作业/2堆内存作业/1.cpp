#include<iostream>

void main()
{
	//1)方法1
	//int* p = 0;//指向数组的首地址
	//int c = 0;//记录整数的个数

	//while(1)
	//{
	//	for(int i = 0; i < c;++i)
	//		std::cout<<p[i]<<std::endl;
	//	int a;
	//	std::cin>>a;

	//	if(0 == p)//首次
	//	{
	//		p = (int*)malloc(sizeof(int));
	//		p[0] = a;
	//	}
	//	else
	//	{
	//		//开辟新的堆
	//		int* q = (int*)malloc(sizeof(int) * (c + 1));
	//		//将原始的数据从原堆中放到新的堆中
	//		for(int i = 0;i < c;++i)
	//			q[i] = p[i];
	//		//将新的数据放入到新的堆中
	//		q[c] = a;
	//		//释放原来的堆
	//		free(p);
	//		//将原来的指针指向新的堆
	//		p = q;
	//	}
	//	++c;
	//}
	//free(p);
	//做法2
	//int s = 8;//数组容量
	////p指向数组首地址
	//int* p = (int*)malloc(s * sizeof(int));
	////整数个数
	//int c = 0;

	//while(1)
	//{
	//	int a;
	//	std::cin>>a;

	//	//扩容判断
	//	if(s == c)//顺序表
	//	{
	//		s *= 2;
	//		//根据确定的新的容量开辟新堆
	//		int* q = (int*)malloc(s * sizeof(int));
	//		//将原堆中的数据移动到新的堆中
	//		for(int i = 0; i < c;++i)
	//			q[i] = p[i];
	//		free(p);
	//		p = q;
	//	}
	//	p[c++] = a;
	//}
	//free(p);

	//2)
	int s = 256;//内存容量
	char* p = (char*)malloc(s);
	int a = 0;//所有字符串的存储空间
	int c = 0;//字符串个数

	while(1)
	{
		char* r = p;
		for(int i = 0; i < c;++i)
		{
			std::cout<<r<<std::endl;
			r += strlen(r) + 1;
		}
		char b[256];
		std::cin>>b;

		if(s - a < strlen(b) + 1)
		{
			s+=strlen(b) + 1;
			s *= 2;
			char* q = (char*)malloc(s);
			memcpy(q,p,a);
			free(p);
			p = q;
		}
		strcpy_s(p + a,s - a,b);
		a += strlen(b) + 1;
		c+=1;
	}
	free(p);

	system("pause");
}
//堆内存的分配和释放是要消耗一定时间的，
//而且容易在内存中形成内存碎片，堆内存
//使用应尽量控制次数