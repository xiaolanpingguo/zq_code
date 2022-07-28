#include <iostream>
#include <conio.h>

#define _QP_W 20 //棋盘宽
#define _QP_H 20 //棋盘高
#define _QP_S (_QP_W * _QP_H) //棋盘大小
#define _YXZT_CSH 0 //游戏状态初始化
#define _YXZT_YX 1 //游戏状态运行
#define _KZ 0 //空子
#define _HZ 1 //黑子
#define _BZ 2 //白子
#define _ZX(x,y) ((x)+(y)*_QP_W) //坐标转下标
#define _XZx(i) ((i)%_QP_W) //下标转x坐标
#define _XZy(i) ((i)/_QP_W) //下标转y坐标

struct _WZQ
{
	char qp[100]; //棋盘数组
	short x : 6, y : 6, c : 1, yxzt : 1;
}; //c为0则表示当前下黑子、为1则表示当前下白子

_WZQ wzq;

//用上面102个字节完成五子棋游戏