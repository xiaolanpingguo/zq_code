// Test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

//引用计数，是很多高级语言中垃圾回收机制的基础

typedef struct _ABC
{
	int num; //存储有多少个指针指向自己
	//...
}* ABC;

ABC createABC()
{
	ABC abc = (ABC)malloc(sizeof(_ABC));
	abc->num = 1; //表示有一个指针指向了本对象
	return abc;
}
ABC evaluateABC(ABC abc)
{
	abc->num += 1; //表示多了一个指针指向了本对象
	return abc;
}
void DestroyABC(ABC abc)
{
	abc->num -= 1;
	if (abc->num == 0) //表示没有指针指向本对象真正可以销毁了
		free(abc);
}

int _tmain(int argc, _TCHAR* argv[])
{
	ABC abc1 = createABC();
	ABC abc2 = evaluateABC(abc1);
	ABC abc3 = evaluateABC(abc1);
	ABC abc4 = evaluateABC(abc1);

	DestroyABC(abc1);
	DestroyABC(abc2);
	DestroyABC(abc3);
	DestroyABC(abc4);

	return 0;
}

