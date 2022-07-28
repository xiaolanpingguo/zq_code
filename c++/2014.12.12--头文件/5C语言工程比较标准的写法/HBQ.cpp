#include "HBQ.h"

#define _IN_QP(x,y) ((x) >= 0 && (x) < _QP_W && (y) >= 0 && (y) < _QP_H)

char qp[_QP_S];//棋盘
char c;//当前颜色

//初始化
void Init()
{
	for(int i = 0; i < _QP_S; ++i)
		qp[i] = _KZ;
	qp[_XY(3,3)] = qp[_XY(4,4)] = _BZ;
	qp[_XY(3,4)] = qp[_XY(4,3)] = _HZ;
	c = _HZ;
}

void Play(int x,int y)
{
	if(_IN_QP(x,y) && qp[_XY(x,y)] == _KZ)
	{
		qp[_XY(x,y)] = c;
		c = (c == _HZ ? _BZ:_HZ);
	}
}