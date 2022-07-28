int add2(int,int);

int add(int a,int b,int c)
{
	return add2(add2(a,b),c);
}

//在工程中没有add2这个函数的定义语句.
//这样的话虽然本文件可以编译通过(因为有
//add2的声明)，但是在最终链接的时候讲失败