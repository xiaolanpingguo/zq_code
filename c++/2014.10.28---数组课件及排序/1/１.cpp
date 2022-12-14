#include<iostream>

void main()
{
	int b;
	b = 10;
	//内存：在内存中开辟了5 * sizeof(int)个字节的连续内存空间，并且
	//将该内存空间的首地址命名为a
	//语言：定义了一个长度为5的int类型的数组a。
	int a[5];

	a[0] = 1;
	a[1] = 2;
	a[2] = 3;
	a[3] = 4;
	a[4] = 5;

	//char a[200];

	//short b[100];

	//double c[30];
	//上面的a数组包含了5个int变量,分别是
	//a[0],a[1],a[2],a[3],a[4],他们是顺次
	//排列在数组中的。也就是说，数组提供了
	//一种一次性定义多个变量的语法，我们使用
	//数组其实就是使用数组中的变量(即元素)
	a[0] = 12;
	a[1] = a[0] * 2;
	a[2] = 4;
	a[3] = a[2] + a[1];
	a[4] = 23;

	//Stack around the variable 'a' was corrupted.
	//a[5] = 44;//数组越界错误
	
	//[]里面的整数称为下标，长度为n的数组
	//的下标的范围是从0到n-1
	
	//注意：
	//在定义时：
	//[]内必须是常量表达式的结果
	//[]内的数字就是数组的长度
	//数组的大小就是数组的数据类型所占字节数乘以数组长度
	//在定义后：
	//[]就被称为下标运算符，[]内的就是下标
	//这个下标可以是任意表达式的结果,只要不
	//越界(超出下标访问的范围)
	//[]内的结果必须是int类型的

	//int c[b];
	//rror C2057: 应输入常量表达式
	//error C2466: 不能分配常量大小为 0 的数组
	//error C2133: “c”: 未知的大小

	const int c = 10;
	int d[c + 1 - 1];

	//a[0.1] = 12;//error C2108: 下标不是整型


	//数组的初始化
	int aa[5] = {1,2,3,4,5};
	//所有的元素（数组中每个变量）的值全部写出来
	//这个时候,数组将把每个值按照数组中每个元素的
	//顺序依次初始化给每个元素
	int bb[5] = {1,2,3};
	//{}中的值的个数如果没有写完，在编译时，将自动
	//把剩下的初始化为0
	int cc[] = {1,2,3,4,5};
	//如果[]内不写长度，则编译时将按照{}内的写的值的
	//个数来确定数组的长度

	//数组初始化和定义的区别
	//定义的时候,[]内必须写值。
	//初始化的时候,[]内可以不写,但如果要写，则必须是
	//常量表达式的结果而且必须是int型的数据

	std::cout<<sizeof(cc)<<std::endl;
	system("pause");
}