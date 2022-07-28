#include "LLK.h"
#include <iostream>
#include <vector>
using namespace std;
vector<CLLK::_NODE> CLLK::open;
vector<CLLK::_NODE> CLLK::close;
#define _ABS(v) ( (v)<0?-(v):(v) )
#define H_VALUE(c,e) (_ABS((c)%w-(e)%w)+_ABS((e)/h-(c)/h))
//获取两个点之间的F值
unsigned int CLLK::_GetMinF()
{
	unsigned int i=0;
	for(unsigned int j=1;j<open.size();++j)
	{
		if(open[i].G+open[i].H>open[j].G+open[j].H)
			i=j;
	}
	return i;
}
//是否在闭表中
bool CLLK::_InClose(int index)
{
	for(int i=0;i<close.size();++i)
		if(close[i].cur == index)
			return true;
	return false;
}
//是否在开表中
int CLLK::_InOpen(int index)
{
	for(int i=0;i<open.size();++i)
		if(open[i].cur == index)
			return i;
	return -1;
}
//两个点之间的路径
int CLLK::FindPath(int *map,int h,int w,int b,int e,int *path)
{
	if(!map || h<1 || w<1 || b<0 || b>=w*h || e<0 || e>=h*w || !path)
		return -1;
	const int offset_x[]={0,1,0,-1};
	const int offset_y[]={-1,-0,1,0};
	open.clear();
	close.clear();
	_NODE begin={b,-1,0,H_VALUE(b,e)};
	open.push_back(begin);
	//开表不为空
	while(!open.empty())
	{
		//获得最小的F值
		unsigned int min_f_i=_GetMinF();
		_NODE min_f_n=open[min_f_i];
		open.erase(open.begin()+min_f_i);
		close.push_back(min_f_n);
		int cx=min_f_n.cur % w;
		int cy=min_f_n.cur / w;
		//循环4个方向
		for(int i=0;i<4;++i)
		{
			int dx=cx+offset_x[i];
			int dy=cy+offset_y[i];
			if(dx>=0 && dx<w && dy>=0 && dy<h)
			{
				int di=dx+dy*w;
				//找到路
				if(di==e)
				{
					//存入闭表
					_NODE node={di,min_f_n.cur,0,0};
					close.push_back(node);
					int index=close.size()-1;
					int pathlen=0;
					//存储路径
					while(index!=-1)
					{
						path[pathlen++]=close[index].cur;
						int j=index;
						int k=close[index].parent;
						if(k==-1)
							break;
						while(1)
						{
							if(close[j].cur==k)
								break;
							else
								--j;
						}
						index=j;
					}
					return pathlen;
				}
				else
				{
					//是通路才找
					if(map[di]==_TL)
					{
						if(!_InClose(di))
						{
							int r=_InOpen(di);
							int curG=min_f_n.G+(i%2==1?7:5);
							if(r==-1)
							{
								_NODE node={di,min_f_n.cur,curG,H_VALUE(di,e)};
								open.push_back(node);
							}
							else
							{
								if(open[r].G<curG)
								{
									open[r].parent=min_f_n.cur;
									open[r].G=curG;
								}
							}
						}
					}
				}
			}
		}
	}
}
