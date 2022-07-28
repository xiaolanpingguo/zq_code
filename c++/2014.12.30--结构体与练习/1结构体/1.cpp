#include<iostream>

//此处定义了一个结构体类型名叫_ABC。此后的代码
//中就可以把_ABC当做一个类型来使用
struct _ABC
{
	char u;
	short i;
	int o;
};//u,i,o称为_ABC类型的成员变量

void main()
{
	int x;
	x = 0;
	_ABC y;
	std::cout<<sizeof(y)<<std::endl;//8
	//使用结构体实际是使用结构体中成员变量
	y.u = 1;
	y.i = 2;
	y.o = 3;
	
	system("pause");
}
//假设有一个游戏，游戏中主角是一队人，则定义主角的数据
//如下：
//  使用基本数据类型处理
//  int hp[8],mp[8],att[8],def[8];
//  要对英雄进行赋值
//  hp[0] = 100;mp[0] = 100;att[0] = 10;def[0] = 10;

//使用结构体
//struct _HERO
//{
//	int hp,mp,att,def;
//};
//
//_HERO hero[8];
//hero[0].hp = 100;
//hero[1].mp = 100;
//hero[2].att = 10;
//hero[3].def = 10;
