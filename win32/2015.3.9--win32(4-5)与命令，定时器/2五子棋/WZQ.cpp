#include "WZQ.h"

int CWZQ::_ZX(int x,int y)
{
	return x + y * _QPW;
}

void CWZQ::Init()
{
	for(int i = 0; i < _QPS;++i)
		qp[i] = _KZ;
	c = _HZ;
}

//落子判断
//_ER : 落子出界或者在该位置有子
//_KZ : 没有胜负
//_HZ : 黑子胜利
//_BZ : 白子胜利

int CWZQ::LuoZi(int x,int y)
{
	if(x < 0 || x > _QPW - 1 
	|| y < 0 || y > _QPH - 1
	|| qp[_ZX(x,y)] != _KZ)
		return _ER;

	qp[_ZX(x,y)] = c;
	for(int i = 0; i < 5 ;++i)
	{
	
	}
	c = (c == _HZ) ? _BZ : _HZ;
	return _KZ;
}

//获取棋盘的数据(用于显示)
const char* CWZQ::getqp()
{
	return qp;
}

//得到当前棋子的颜色
char CWZQ::getc()
{
	return c;
}