#ifndef _2_H_
#define _2_H_

extern int a;
void b();

//如果光是全局变量或函数的声明的话，用不用#ifndef、#define、#endif
//都可以，但是头文件中我们往往还要写复合数据类型的类型定义，而这种
//类型定义虽然不分配内存只规定结构，但是依然是一个定义，在cpp中只能
//出现一次，所以为了使得我们的头文件在cpp中只出现一次，就用#ifndef、
//#define、#endif对其进行包围
struct c
{
	int x, y, z;
};

#endif