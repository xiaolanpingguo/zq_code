#define _MAP_MIN_W 5 //地图宽下限
#define _MAP_MAX_W 20 //地图宽上限
#define _MAP_MIN_H 5 //地图高下限
#define _MAP_MAX_H 20 //地图高上限

#define _TCS_INPUT_NONE 0 //无指令
#define _TCS_INPUT_UP 1 //上指令
#define _TCS_INPUT_DOWN 2 //下指令
#define _TCS_INPUT_LEFT 3 //左指令
#define _TCS_INPUT_RIGHT 4 //右指令

#define _KD 0 //空地
#define _ZA 1 //障碍
#define _ST 2 //蛇头
#define _SS 3 //蛇身
#define _GZ 4 //果子

//贪吃蛇初始化函数
//mapW:地图宽
//mapH:地图高
//返回:成功或失败(宽、高不合符要求将导致失败)
bool tcsInit(int mapW, int mapH);

//贪吃蛇运行函数
//input:输入,_TCS_INPUT_NONE、_TCS_INPUT_UP、
//_TCS_INPUT_DOWN、_TCS_INPUT_LEFT、
//_TCS_INPUT_RIGHT分别代表
//无输入、上、下、左、右
//返回:-3代表没有初始化、
//-2代表输入错误、
//-1代表蛇头咬了蛇身、
//0代表撞着了障碍、1代表正常、
//2代表吃了一个果子
int tcsRun(int input);

//贪吃蛇重置函数
//返回:成功或失败(没有初始化将导致失败)
bool tcsRestart();

//贪吃蛇得到地图函数
//返回:0或地图数组首地址,
//用于绘制(没有初始化将导致返回0)
const char* tcsMap();
