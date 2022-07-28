#include <iostream>
#include <windows.h>

void main()
{
	int* p = (int*)malloc(4);

	*p = 100; //64 00 00 00

	//仅仅是将p所指向的内存单元设置为不可使用，但是
	//不会对p进行修改，p依然指向那块堆内存
	free(p); //一旦指针释放我们一般需要将其归零p = NULL;

	if (p)
		std::cout<<"没有释放"<<std::endl;
	else
		std::cout<<"释放了 "<<std::endl;
	
	system("pause");
}