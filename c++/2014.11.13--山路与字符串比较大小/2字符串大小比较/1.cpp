#include<iostream>

//字符串大小的比较规则

void main()
{
	//字符串是有大小的不同
	"abcdef";
	"accd"; //上面的小于于下面的
	"abcdef";
	"abcdee";//上面的大于下面的
	"abcdee";//上面等于下面的
	"abd";//下面的大于上面的
	
	//字符串的比较(字典比较法)是依次比较每个字节的大小
	//01)若有大小的区分，则立即停止比较，那个字符串
	//的字节大就算这个字符串大
	//02)若本次比较是相同的，那么继续比较下一个字节
	//直到结束符都参与了比较如果还相等，那么这个两个
	//字符串就相等
	
	//下面的比较不是字典比较法，是按照地址来比的

	if("abcdef" >"abd" )
		std::cout<<"1"<<std::endl;

	if("abcdef" > "accd")
		std::cout<<"2"<<std::endl;

	if("abcdef" < "abcdee")
		std::cout<<"3"<<std::endl;
	system("pause");
}