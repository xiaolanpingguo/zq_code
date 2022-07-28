#define _QP_W 8
#define _QP_H 8
#define _QP_S (_QP_W * _QP_H)

#define _KZ 0
#define _HZ 1
#define _BZ 2

extern char qp[_QP_S];
extern char c;//当前棋子

//初始化
void HBQ_Init();

//x,y传入的数据有错误返回-2
//当前位置不能落子返回-1
//落子成功但没有胜负返回0
//落子成功有胜负返回1
int HBQ_Play(int x,int y);