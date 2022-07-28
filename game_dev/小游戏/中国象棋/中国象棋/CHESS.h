#ifndef _CHSEE_H_
#define _CHESS_H_
//红方与蓝方
#define _HF 0
#define _LF 1
//蓝方的棋子元素
#define L_JIANG 1
#define L_SHI 2
#define L_XIANG 3
#define L_MA 4
#define L_JU 5
#define L_PAO 6
#define L_BING 7
//选中棋子
#define _XZ 8
//红方棋子元素
#define H_SHUAI -1
#define H_SHI -2
#define H_XIANG -3
#define H_MA -4
#define H_JU -5
#define H_PAO -6
#define H_BING -7
#define QP_W 9
#define QP_H 10
#define QP_S (QP_W)*(QP_H)
#define IN_QP(x,y) ((x) >= 0 && (x) < QP_W && (y) >= 0 && (y) < QP_H) 
//棋盘数组
extern int qp[QP_S];
//当前下棋方
extern char qz;
//帅和将的下子规则
bool wang(int b_x,int b_y,int e_x,int e_y);
//仕的下子规则
bool shi(int b_x,int b_y,int e_x,int e_y);
//相的下子规则
bool xiang(int b_x,int b_y,int e_x,int e_y);
//马的下子规则
bool ma(int b_x,int b_y,int e_x,int e_y);
//车的下子规则
bool ju(int b_x,int b_y,int e_x,int e_y);
//炮的下子规则
bool pao(int b_x,int b_y,int e_x,int e_y);
//兵的下子规则
bool bing(int b_x,int b_y,int e_x,int e_y);
//初始化函数
void InitQp();
//获取棋盘
int *GetQp();
#endif