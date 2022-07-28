#include <iostream>
#include "A.h"
#include "B.h"
//类A 类B
//类A中希望B类的指针作为其形式参数，成员变量。
//而B中希望A类的指针作为其形式参数，成员变量
//只需要前置声明就可以


//类相互之间不能包含类对象，但可以包含指针，
//这样只需要前置声明就可以
void main()
{
	A x;
	x.aa();
	B y;
	y.bb();

	system("pause");
}


