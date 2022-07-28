#include "Astar.h"

std::vector<AStar::_NODE> AStar::open;
std::vector<AStar::_NODE> AStar::close;

#define _ABS(v) ((v) < 0 ? -(v) : (v))
#define _H_VALUE(c,e) (_ABS((c)%w - (e)%w) + _ABS((c)/w - (e)/w))


unsigned int AStar::_GetMinF()
{
	unsigned int i = 0;
	for(unsigned int j = 1;j < open.size();++j)
	{
		if((open[i].G + open[i].H) > (open[j].G + open[j].H))
			i = j;
	}
	return i;
}
bool AStar::_InClose(int index)
{
	for(int i = 0; i < close.size();++i)
	{
		if(index == close[i].cur)
			return true;
	}
	return false;
}
int AStar::_InOpen(int index)
{
	for(int i = 0; i < open.size();++i)
	{
		if(index == open[i].cur)
			return i;
	}
	return -1;
}

//如果返回-1表示参数有问题，
//如果返回0则表示没有找到路
//如果返回大于0表示找到路并返回路长
int AStar::FindPath(const char* map,//地图
						int w,//地图的宽
						int h,//地图高
						int b,//寻路开始位置
						int e,//寻路结束位置
						int* path)//存储寻到路径点
{
	if(!map || w < 1 || h < 1|| b < 0 || b >= w * h || e < 0 || e >= w * h || !path)
		return -1;

	//八方向偏移
	// 701
	// 6 2
	// 543
	
	const int offset_x[] = 
	{
		0,1,1,1,0,-1,-1,-1
	};
	const int offset_y[] =
	{
		-1,-1,0,1,1,1,0,-1	
	};

	//清空开表闭表
	open.clear();
	close.clear();

	//起点入开表
	_NODE begin = {b,-1,0,_H_VALUE(b,e)};

	open.push_back(begin);
	//寻路循环
	while(!open.empty())
	{
		//得到开表中F值最小的节点的下标
		unsigned int min_f_i = _GetMinF();
		//将开表中F值最小的那个节点删除
		_NODE min_f_n = open[min_f_i];
		//std::vector <_NODE>::iterator it = open.begin();
		//open.erase(it + min_f_i);
		open.erase(open.begin() + min_f_i);
		//放入闭表
		close.push_back(min_f_n);
		//得到当前这个节点的坐标
		int cx = min_f_n.cur % w;
		int cy = min_f_n.cur / w;
		//循环当前点的八个方向
		for(int i = 0; i < 8 ; ++i)
		{
			int dx = cx + offset_x[i];
			int dy = cy + offset_y[i];
			if(dx >= 0 && dx < w && dy >= 0 && dy < h)
			{
				//找到路
				int di = dx + dy * w;
				if(di == e)
				{
					//终止点入闭表
					_NODE node = {di,min_f_n.cur,0,0};
					close.push_back(node);
					//最后放入的节点的下标
					int index = close.size() - 1;
					//循环得到路
					int pathlen = 0;
					while(index != -1)
					{
						path[pathlen++] = close[index].cur;
						int j = index;
						int k = close[index].parent;
						if(k == -1)
							break;

						while(1)
						{
							if(close[j].cur == k)
								break;
							else 
								--j;
						}
						index = j;
					}

					return pathlen;
				}
				else
				{
					//不是障碍
					if(map[di] > 0)
					{
						//不在闭表中
						if(!_InClose(di))
						{
							
							int r = _InOpen(di);
							int curG = min_f_n.G + (i % 2 == 1 ? 7 : 5);
							//不在开表中
							if(r == -1)
							{
								_NODE node = {di,min_f_n.cur,curG,_H_VALUE(di,e)};
								open.push_back(node);
							}
							else
							{
								//如果当前的G值比在开表中的G小，
								//则更新G值
								if(open[r].G < curG)
								{
									open[r].parent = min_f_n.cur;
									open[r].G = curG;
								}
							}
						}
					}
				}
			}
		}
	}
	return 0;
}