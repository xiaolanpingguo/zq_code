//该游戏主要的逻辑部分需要的一些宏
//全局变量，函数的声明(不只是本模块用到
//其他模块可能也用的到)
//如果只有本身能用到的在该模块的cpp文件中
//定义
#define _MAP_W 3   //地图宽
#define _MAP_H 3   //地图高
#define _MAP_S (_MAP_W * _MAP_H) //地图总大小

#define _KD 0  //空地
#define _LS 1  //老鼠
#define _GJ 2  //攻击
#define _SW 3  //死亡

extern char map[_MAP_S];//地图
extern bool input[9];//输入状态
extern int hp,score;//血量，分数

void Game_Init();//游戏初始化

void Game_Logic();//游戏逻辑
