#include<iostream>

//结构体的sizeof大小
//为了使得访问结构体对象中的成员变量比较高效,
//结构体中的成员变量的内存的分布采取了一种叫
//"内存对齐"的处理策略
//1)每个成员变量的字节下标必须是自己大小的整数
//倍，如果不是就在前面添加一定的无用字节
//2)整个结构体对象的大小必须是最大成员变量大小的
//整数倍，如果不是就在最后添加一定的无用字节
struct _ABC1
{
	char a;//[a]
	short b;//<>[b][b]
	int c;//[c][c][c][c]
};

struct _ABC2
{
	char a;//[a]
	int b;//<><><>[b][b][b][b]
	short c;//[c][c]<><>
};

void main()
{
	std::cout<<sizeof(_ABC1)<<std::endl;
	std::cout<<sizeof(_ABC2)<<std::endl;

	//01 ?? ?? ?? 02 00 00 00 03 00 ?? ??
	_ABC2 x = {1,2,3};
	system("pause");
}
