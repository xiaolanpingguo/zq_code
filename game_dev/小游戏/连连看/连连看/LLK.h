#ifndef _LLK_H
#define _LLK_H
//障碍
#define _ZA 11
//通路
#define _TL 12
//路径
#define _LJ 13
#define _XX 1 //星星
#define _LX 2 //菱形
#define _YX 3 //圆形
#define _SJ 4 //三角形
#define _FK 5 //方块
//选中各个图案后的显示
#define S_XX 6 //实心星星
#define S_LX 7 //实心菱形
#define S_YX 8 //实心圆形
#define S_SJ 9 //实心三角形
#define S_FK 10 //实心方块
#define MAP_W 12
#define MAP_H 12
#define MAP_S (MAP_W) *(MAP_H)
#include <vector>
using namespace std;
class CLLK
{
	struct _NODE
	{
		int cur;
		int parent;
		int G;
		int H;
	};
	static vector<_NODE> open;
	static vector<_NODE> close;
	static unsigned int _GetMinF();
	static bool _InClose(int index);
	static int _InOpen(int index);
public:
	static int FindPath(int *map,int w,int h,int b,int e,int *path);
};
#endif