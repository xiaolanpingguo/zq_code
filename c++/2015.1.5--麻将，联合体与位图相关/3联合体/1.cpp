#include <iostream>

//此次定义了一种联合体类型，其后就可以
//用这种联合体类型来定义对象
union _ABC
{
	char a;
	short b;
	int c;
};

union _IP_ADDRESS
{
	unsigned int ip1;
	unsigned short ip2[2];
	unsigned char ip3[4];
};

void main()
{
	//联合体中所有成员变量都共用一段内存，这段内存
	//的大小就是最大的成员变量的大小,比如上面的_ABC
	//的大小就是sizeof(int)
	_ABC x;
	x.a = 1;// 01 ?? ?? ??
	x.b = 2;// 02 00 ?? ??
	x.c = 3;// 03 00 00 00 
	x.b = 2;// 02 00 00 00
	//std::cout<<sizeof(x)<<std::endl;
	std::cout<<(int)x.a<<std::endl;
	std::cout<<x.b<<std::endl;
	std::cout<<x.c<<std::endl;
	_ABC* y = &x;
	y->c = 4;// 04 00 00 00
	y->b = 5;// 05 00 00 00
	y->a = 6;// 06 00 00 00
	//联合体中最后被写的成员变量就是能够被正确
	//读取的成员变量，其它内容和结构体完全一样
	//注意，上面的ip地址联合体可以有多种表示方式
	//比如用4个unsigned char来进行标示的话可以方便
	//用户填写读取ip地址
	_IP_ADDRESS ipA,ipB;
	ipA.ip3[0] = 192;
	ipA.ip3[1] = 168;
	ipA.ip3[2] = 1;
	ipA.ip3[3] = 100;//192 168 1 100

	ipB.ip3[0] = 192;
	ipB.ip3[1] = 168;
	ipB.ip3[2] = 1;
	ipB.ip3[3] = 101;// 192 168 1 101
	//但上面的表示方式就不太适合比较IP之类的操作
	//而这种操作最好用ip1来进行是最节约时间的

	//if(ipA.ip3[0] == ipB.ip3[0]
	//&&ipA.ip3[1] == ipB.ip3[1]
	//&&ipA.ip3[2] == ipB.ip3[2]
	//&&ipA.ip3[3] == ipB.ip3[3])

	//if(ipA.ip1 == ipB.ip1)的效率比上面要高

	std::cout<<sizeof(_IP_ADDRESS)<<std::endl;

	system("pause");
}