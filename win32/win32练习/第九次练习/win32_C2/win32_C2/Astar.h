#ifndef _A_STAR_H_
#define _A_STAR_H_
#include <vector>

class AStar
{
	struct _NODE
	{
		int cur;
		int parent;
		int G;
		int H;
	};

	static std::vector<_NODE> open;
	static std::vector<_NODE> close;
	static unsigned int _GetMinF();
	static bool _InClose(int index);
	static int _InOpen(int index);

public:
	//如果返回-1表示参数有问题，
	//如果返回0则表示没有找到路
	//如果返回大于0表示找到路并返回路长
	static int FindPath(const char* map,//地图
						int w,//地图的宽
						int h,//地图高
						int b,//寻路开始位置
						int e,//寻路结束位置
						int* path);//存储寻到路径点
};



#endif