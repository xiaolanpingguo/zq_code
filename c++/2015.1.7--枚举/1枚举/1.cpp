#include<iostream>

//union _ABC
//{
//	int a;
//	short b;
//	double c;
//};

//枚举 enum

//枚举是一种类型及其取值范围
//枚举的本质是int
//取值必须是合法的标识符

enum _ABC
{
	abc1, //0 最初的取值会被设置为0，后面的取值
	abc2, //1 依次递增
	abc3, //2
	abc4  //3
};

void main()
{
	_ABC x = abc1;
	x = abc2;
	_ABC y = abc3;
	y = abc4;
	//y = 2;//虽然枚举的本质是int，但不能被int赋值
	x = y;
	//x = x + y;//_ABC + _ABC ->隐式转换 》int+int
	
	x + y;//

	int b = sizeof(x);
	//++x;
	x && y;
	x == y; //这里是枚举主要使用的运算符!!!!!!!!!
	x ? 1:2;
	1 ? x:y;
	x & y;
	//x += y;

	_ABC* z = &x;
	y = *z;
	_ABC t[3];
	t[0] = x;

	//以五子棋为例

#define _KZ 0
#define _HZ 1
#define _BZ 2

	char qp1[400];

	qp1[0] = 3;//这里可以赋值，但从游戏角度来说是错误的，因为不知道这是什么，但
	//编译器发现不了这个问题

	enum _QIZI
	{
		_QI_KZ,
		_QI_HZ,
		_QI_BZ
	};

	_QIZI qp2[400];
	qp2[0] = _QI_KZ;
	qp2[1] = _QI_HZ;
	qp2[2] = _QI_BZ;
	//qp2[2] = 3;//利用枚举来强制约束我们的类型可以被赋的值，
	system("pause");
}