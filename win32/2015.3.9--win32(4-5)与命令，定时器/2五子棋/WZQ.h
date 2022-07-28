#ifndef _WZQ_H_
#define _WZQ_H_

#define _ER -1
#define _KZ 0
#define _HZ 1
#define _BZ 2

#define _QPW 20
#define _QPH 20

#define _QPS (_QPW * _QPH)


class CWZQ
{
	char qp[_QPS];//棋盘
	char c;//当前棋子的颜色

	int _ZX(int x,int y);
	
public:
	void Init();

	//落子判断
	//_ER : 落子出界或者在该位置有子
	//_KZ : 没有胜负
	//_HZ : 黑子胜利
	//_BZ : 白子胜利
	int LuoZi(int x,int y);

	//获取棋盘的数据(用于显示)
	const char* getqp();

	//得到当前棋子的颜色
	char getc();
};

#endif