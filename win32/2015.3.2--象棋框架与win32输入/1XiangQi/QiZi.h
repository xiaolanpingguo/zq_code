#ifndef _QIZI_H_
#define _QIZI_H_
//棋子的父类，所有的棋子都继承自这个类。并实现其本身的逻辑
class CQiZi
{
	int m_iQiZiX;//棋子的X坐标
	int m_iQiZiY;//棋子的Y坐标
public:
	//棋子的逻辑
	virtual bool Logic(int x,int y);
};

#endif