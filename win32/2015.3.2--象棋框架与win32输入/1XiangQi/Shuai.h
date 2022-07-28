#ifndef _SHUAI_H_
#define _SHUAI_H_
#include "QiZi.h"

//帅
class CShuai : public CQiZi
{
	int m_iQiZiX;//棋子的X坐标
	int m_iQiZiY;//棋子的Y坐标
public:
	//棋子的逻辑
	bool Logic(int x,int y);
};

#endif