#include <iostream>
#include"CHESS.h"
int qp[QP_S]=
{
	5,4,3,2,1,2,3,4,5,
	0,0,0,0,0,0,0,0,0,
	0,6,0,0,0,0,0,6,0,
	7,0,7,0,7,0,7,0,7,
	0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,
	-7,0,-7,0,-7,0,-7,0,-7,
	0,-6,0,0,0,0,0,-6,0,
	0,0,0,0,0,0,0,0,0,
	-5,-4,-3,-2,-1,-2,-3,-4,-5
};
char qz;
//帅和将
bool wang(int b_x,int b_y,int e_x,int e_y)
{
	const int offset_x[]={0,1,0,-1};
	const int offset_y[]={-1,0,1,0};
	for(int i=0;i<4;++i)
	{
		int cx=offset_x[i]+b_x;
		int cy=offset_y[i]+b_y;
		//帅的活动范围
		if(qz==_HF)
		{
			if(cx>=3 && cx<=5 && cy<QP_H && cy>QP_H-4)
			{
				if(cx==e_x && cy == e_y)
					return true;
			}
		}
		//将的活动范围
		else
		{
			if(cx>=3 && cx<=5 && cy<3 && cy>=0)
			{
				if(cx==e_x && cy == e_y)
					return true;
			}
		}
	}
	return false;
}
//仕
bool  shi(int b_x,int b_y,int e_x,int e_y)
{
	const int offset_x[]={1,1,-1,-1};
	const int offset_y[]={-1,1,1,-1};
	for(int i=0;i<4;++i)
	{
		int cx=offset_x[i]+b_x;
		int cy=offset_y[i]+b_y;
		if(qz==_HF)
		{
			//仕的活动范围
			if(cx>=3 && cx<=5 && cy<=9 && cy>=7)
			{
				//仕的十字没有棋子
				if(cx==e_x && cy == e_y && (qp[76]==0||qp[76]==_XZ))
					return true;
			}
		}
		else
		{
			if(cx>=3 && cx<=5 && cy<3 && cy>=0)
			{
				if(cx==e_x && cy == e_y && (qp[14]==0||qp[14]==_XZ))
					return true;
			}
		}
	}
	return false;
}
//相
bool  xiang(int b_x,int b_y,int e_x,int e_y)
{
	//相先判断是否田字中间有棋子
	const int offset_x[]={1,1,-1,-1};
	const int offset_y[]={-1,1,1,-1};
	const int pd_x[]={2,2,-2,-2};
	const int pd_y[]={-2,2,2,-2};
	for(int i=0;i<4;++i)
	{
		int cx=offset_x[i]+b_x;
		int cy=offset_y[i]+b_y;
		bool flag=false;
		//红方相的活动范围
		if(qz==_HF)
		{
			if(cx>=0 && cx<QP_W && cy<QP_H && cy>QP_H-6)
			{
				//田字中间没有棋子
				if(qp[cx+cy*QP_W]==0)
				{
					if(b_x+pd_x[i]==e_x && b_y+pd_y[i] == e_y)
						return true;
				}
			}
		}
		//蓝方相
		else
		{
			if(cx>=0 && cx<=QP_W && cy<5 && cy>=0)
			{
				if(cx>=0 && cx<=QP_W && cy<5 && cy>=0)
				{
					if(qp[cx+cy*QP_W]==0)
					{
						if(cx+offset_x[i]==e_x && cy+offset_y[i] == e_y)
							return true;
					}
				}
			}
		}
	}
	return false;
}
//车
bool ju(int b_x,int b_y,int e_x,int e_y)
{
	//车的四个方向偏移量
	const int offset_x[]={0,1,0,-1};
	const int offset_y[]={-1,0,1,0};
	for(int i=0;i<4;++i)
	{
		bool flag=false;
		bool flag1=false;
		int cx=offset_x[i]+b_x;
		int cy=offset_y[i]+b_y;
		//在一个方向上从开始坐标找到第一个有棋子的地方
		for(;IN_QP(cx,cy);cx+=offset_x[i],cy+=offset_y[i])
		{
			if(qp[cx+QP_W*cy]!=0)
			{
				flag=true;
				flag1=true;
				break;
			}
			else
				flag1=false;
		}
		//找到这个棋子后，标志车的活动范围
		if(flag)
		{
			for(;cx!=b_x||cy!=b_y;cx-=offset_x[i],cy-=offset_y[i])
			{
				if(cx==e_x && cy==e_y)
				{
					return true;
				}
			}
		}
		//一个方向上没有棋子，即可以再这个方向的任意位置移动
		else if(!flag1)
		{
			for(;cx!=b_x||cy!=b_y;cx-=offset_x[i],cy-=offset_y[i])
			{
				if(cx==e_x && cy==e_y)
				{
					return true;
				}
			}
		}
	}
	return false;
};
//马
bool ma(int b_x,int b_y,int e_x,int e_y)
{
	//马一个直线是否有棋子，4个方向的偏移量
	const int pd_x[]={0,1,0,-1};
	const int pd_y[]={-1,0,1,0};
	//马踩日的8个方向偏移量
	const int offset_x[]={-1,1,2,2,1,-1,-2,-2,};
	const int offset_y[]={-2,-2,-1,1,2,2,1,-1,};
	for(int i=0;i<4;++i)
	{
		int px=pd_x[i]+b_x;
		int py=pd_y[i]+b_y;
		//该条直线没有棋子，即可以跳马
		if(IN_QP(px,py) && qp[px+py*QP_W]==0)
		{
			//两个数组偏移量的关系为二倍关系
			int j=2*i;
			if( (b_x+offset_x[j]==e_x &&b_y+offset_y[j]==e_y)||
				(b_x+offset_x[j+1]==e_x &&b_y+offset_y[j+1]==e_y) )
				return true;
		}
	}
	return false;
}
//炮
bool pao(int b_x,int b_y,int e_x,int e_y)
{
	const int offset_x[]={0,1,0,-1};
	const int offset_y[]={-1,0,1,0};
	for(int i=0;i<4;++i)
	{
		bool flag=false;
		bool flag1=false;
		int cx=offset_x[i]+b_x;
		int cy=offset_y[i]+b_y;
		//从开始坐标找到一条直线的第一个棋子
		for(;IN_QP(cx,cy);cx+=offset_x[i],cy+=offset_y[i])
		{
			if(qp[cx+QP_W*cy]!=0)
			{
				flag=true;
				break;
			}
		}
		//利用该棋子，即炮可以进行吃掉棋子
		if(flag)
		{
			cx+=offset_x[i],cy+=offset_y[i];
			for(;IN_QP(cx,cy);cx+=offset_x[i],cy+=offset_y[i])
			{
				if(qp[cx+QP_W*cy]!=0)
				{
					flag1=true;
					break;
				}
			}
			if(flag1 && cx==e_x && cy==e_y)
			{
				return true;
			}
		}
	}
	//如果一条直线没有棋子，即跟车的下子规则一样
	if(ju( b_x, b_y, e_x, e_y))
		return true;
	return false;
}
//兵
bool bing(int b_x,int b_y,int e_x,int e_y)
{
	//红方兵，三个方向，没有下方向
	const int hf_x[]={0,1,-1};
	const int hf_y[]={-1,0,0};
	//蓝方兵，三个方向，没有上方向
	const int lf_x[]={1,0,-1};
	const int lf_y[]={0,1,0};
	//红方兵活动范围
	if(qz==_HF)
	{
		//没有“过河”
		if(b_y<=6 && b_y>=5)
		{
			if(b_x+hf_x[0]==e_x && b_y+hf_y[0]==e_y)
				return true;
		}
		//过河
		else
		{
			for(int i=0;i<3;++i)
			{
				int cx=hf_x[i]+b_x;
				int cy=hf_y[i]+b_y;
				if(cx>=0 && cx<QP_W && cy>=0 && cy<=6)
				{
					if(cx==e_x && cy==e_y)
						return true;
				}
			}
		}
	}
	//蓝方兵
	else
	{
		if(b_y<=4 && b_y>=3)
		{
			if(b_x+lf_x[1]==e_x && b_y+lf_y[1]==e_y)
				return true;
		}
		else
		{
			for(int i=0;i<3;++i)
			{
				int cx=lf_x[i]+b_x;
				int cy=lf_y[i]+b_y;
				if(cx>=0 && cx<QP_W && cy>=3 && cy<QP_H)
				{
					if(cx==e_x && cy==e_y)
						return true;
				}
			}
		}
	}
	return false;
}
//初始化棋盘
void InitQp()
{
	int qp[QP_S]=
	{
		5,4,3,2,1,2,3,4,5,
		0,0,0,0,0,0,0,0,0,
		0,6,0,0,0,0,0,6,0,
		7,0,7,0,7,0,7,0,7,
		0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,
		-7,0,-7,0,-7,0,-7,0,-7,
		0,-6,0,0,0,0,0,-6,0,
		0,0,0,0,0,0,0,0,0,
		-5,-4,-3,-2,-1,-2,-3,-4,-5
	};
	qz=_HF;
}
//获得棋盘
int* GetQp()
{
	return qp;
}
