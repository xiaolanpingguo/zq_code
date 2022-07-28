#define ABC 123
extern int x;
void f();

//会导致1.cpp和2.cpp中都出现一个叫y的int类型的全局变量，将导致链接失败
//int y;

//源文件写定义
//头文件写声明