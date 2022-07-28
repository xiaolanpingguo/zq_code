#include<iostream>

void main()
{
	bool a = true;//01
	short b = 12345;//39 30
	int c = 123456789;//15 CD 5B 07

	char d[7] = {};//00 00 00 00 00 00 00
	
	//将d这个char地址强制转换为bool地址再初始化bool指针e
	bool* e = (bool*)d;

	*d = 'a';//61 00 00 00 00 00 00

	*e = a;//01 00 00 00 00 00 00

	//将d这个char地址强制转换为short地址,
	//再在这个地址上加上1(2个字节)然后在
	//初始化给short指针f
	short* f = (short*)d + 1;

	*f = 12345;//01 00 39 30 00 00 00

	//将e这个bool地址加1后强制转换为short地址
	//在赋值给f
	f = (short*)(e + 1);//

	*f = b;//01 39 30 30 00 00 00

	*((int*)(d + 3)) = c;//01 39 30 15 CD 5B 07
	
	//d依然是char*类型，也就是char类型的地址
	//(Y类型*)(X类型地址)的结果是一个Y类型的地址
	//其字节编号和()内的X类型地址的字节编号相同.
	system("pause");
}