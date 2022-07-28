#include <iostream>

//sizeof
//1)可以得到一个类型所占据字节的数量
//2)可以得到一个表达式结果所占据字节的数量
//3)若sizeof与数组在同一函数中,则sizeof(数
//  组名)可以得到这个数组的总大小(按字节算)

void main()
{
	int a[5];
	std::cout<<sizeof(a)<<std::endl; //sizeof(int) * 数组长度  sizeof (a) / sizeof (int)  数组元素的长度

	double b[3];

	std::cout<<sizeof(b)<<std::endl;
	

	system("pause");
}