#ifndef _MINE_H_
#define _MINE_H_

//地雷结构-每个格子的状态
struct _MINE 
{
	bool is_mine;//是否为雷
	bool is_open;//是否打开
	char mine_num;//周围的雷数
};

//整个地图结构-整个地图的状态
typedef struct _MINE_GAME
{
	int w,h,num;//地图宽，高，总雷数
	_MINE* map;//地图
	int* help;//辅助数组
	
}* MINEGAME;

//创建地图-w:宽,h：高，num:雷数
//地图地址
MINEGAME createMINEGAME(int w,int h,int num);

//MINEGAME的地址
//返回-1,0,1代表失败，正常，通关
int playMINEGAME(MINEGAME mg,int x,int y);

//结束
void endMINEGAME(MINEGAME mg);
#endif
//整个头文件源文件只涉及到游戏的数据以及逻辑，不涉及游戏的输入
//输出。目的在于方便移植，因为输入输出和系统关系比较密切，如果在
//模块中写了输入输出，那么一旦我们希望这份代码在其他操作系统环境下
//也能使用，那么就需要进行输入输出修改，这样就不方便.