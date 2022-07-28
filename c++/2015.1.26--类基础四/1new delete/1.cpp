#include <iostream>

class A
{
	char x;
	short y;
public:
	A()
	{
		std::cout<<"无参构造"<<std::endl;
	}
	A(int a)
	{
		std::cout<<"A的带参构造"<<std::endl;
	}
	~A()
	{
		std::cout<<"析构"<<std::endl;
	}
};

void main()
{
	//malloc	
	//分配sizeof(类名)这么大的堆内存空间
	A* p0 = (A*)malloc(sizeof(A));

	//释放内存
	free(p0);

	//new 
	//delete

	//new的作用
	//1)分配sizeof(A)这么大的堆内存空间
	//2)执行构造
	A* p1 = new A;//4字节
	//int* a = new int;
	//char* a = new char;
	//double* a = new double;
	//delete的作用
	//01)调用析构
	//02)释放堆内存空间
	delete p1;
	//delete a;

	//new ?[num]的作用
	//01)分配sizeof(A)*num个堆内存空间
	//02)依次在每个类对象中执行构造
	int num = 3;
	A* p2 = new A[num];
	//int* a = new int[10];
	//char* a = new char[10];
	//double* a = new double[10];

	//delete []?的作用
	//01)依次执行每个类对象的析构
	//02)释放堆内存空间
	delete []p2;
	//delete []a
	system("pause");
}