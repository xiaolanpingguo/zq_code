#include <iostream>
#include "CHESS.h"
#include <conio.h>
#include <Windows.h>
using namespace std;
void main()
{
	//控制台颜色指针
	HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);
	int GameState=0;
	//x,y--红方移动坐标
	//x1,y1--蓝方移动坐标
	int x=0,x1=0,y=QP_H-1,y1=0;
	//b_x,b_y--记录选中的棋子坐标
	//e_x,e_y--记录棋子将要移动的终点坐标
	int b_x,b_y,e_x,e_y;
	//选中棋子的标志
	bool begin=false;
	//记录选中的棋子
	int value;
	//记录红方上次下子的坐标
	int h_pos;
	//记录蓝方上次下子的坐标
	int l_pos;
	cout<<"即将开始中国象棋，";
	system("pause");
	while(1)
	{
		system("cls");
		if(GameState ==0)
		{
			InitQp();
			GameState=1;
			l_pos=x1+y1*QP_W;
			h_pos=x+y*QP_W;
		}
		else
		{
			//得到颜色
			SetConsoleTextAttribute(h, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
			cout<<"-------中国象棋--------"<<endl;
			cout<<"-------操作说明-------"<<endl;
			cout<<"红方按键--W:上   A:左   S:下   D:右 "<<endl;
			cout<<"绿方按键--I:上   J:左   K:下   L:右 "<<endl;
			cout<<"Space：选中棋子  N:退出"<<endl<<endl;
			int *p=GetQp();
			int pos=(qz==_HF?h_pos:l_pos);
			for(int i=0;i<QP_S;++i)
			{
				if(i==pos)
				{
					SetConsoleTextAttribute(h, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
					cout<<"棋";
				}
				else
				{
					//得到棋子颜色与绘制地图
					if(p[i]>0)
						SetConsoleTextAttribute(h,FOREGROUND_GREEN);
					else if(p[i]<0)
						SetConsoleTextAttribute(h,FOREGROUND_RED);
					else
						SetConsoleTextAttribute(h, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
					switch (p[i])
					{
					case 0:cout<<"┿";break;
					case _XZ:cout<<"○";break;
					case L_JIANG:cout<<"将";break;
					case H_SHUAI:cout<<"帅";break;
					case L_JU:cout<<"车";break;
					case L_MA:cout<<"马";break;
					case L_PAO:cout<<"炮";break;
					case L_SHI:cout<<"仕";break;
					case L_XIANG:cout<<"相";break;
					case L_BING:cout<<"兵";break;
					case H_JU:cout<<"车";break;
					case H_MA:cout<<"马";break;
					case H_PAO:cout<<"炮";break;
					case H_SHI:cout<<"仕";break;
					case H_XIANG:cout<<"相";break;
					case H_BING:cout<<"兵";break;
					}
				}
				if(i%QP_W == QP_W-1)
					cout<<endl;
			}
			SetConsoleTextAttribute(h, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
			cout<<endl<<"当前出手：";
			if(qz==_LF)
					SetConsoleTextAttribute(h,FOREGROUND_GREEN);
			else 
					SetConsoleTextAttribute(h,FOREGROUND_RED);
			cout<<(qz==_HF?"红方":"绿方")<<endl;
			char input=_getch();
			if((input == 'N' || input =='n') && y>0)
			{
				cout<<"确认要退出游戏吗,退出按y或Y，返回游戏请按任意键"<<endl;
				char sel=_getch();
				if(sel=='Y' || sel=='y')
					break;
				else
					continue;
			}
			//红方下棋
			if(qz==_HF)
			{
				if((input == 'W' || input =='w') && y>0)
					y--;
				if((input == 'S' || input =='s') && y<QP_H-1)
					y++;
				if((input == 'A' || input =='a') && x>0)
					x--;
				if((input == 'D' || input =='d') && x<QP_W-1)
					x++;
				h_pos=x+y*QP_W;
			}
			//蓝方下棋
			else
			{
				if((input == 'I' || input =='i') && y1>0)
					y1--;
				if((input == 'K' || input =='k') && y1<QP_H-1)
					y1++;
				if((input == 'J' || input =='j') && x1>0)
					x1--;
				if((input == 'L' || input =='l') && x1<QP_W-1)
					x1++;
				l_pos=x1+y1*QP_W;
			}
			if(input == ' ')
			{
				//选中棋子
				if(!begin  && ((qz==_HF &&qp[x+y*QP_W]<0) ||(qz==_LF &&qp[x1+y1*QP_W]>0)))
				{
					if(qz==_HF)
					{
						b_x=x;
						b_y=y;
					}
					else
					{
						b_x=x1;
						b_y=y1;
					}
					//记录棋子
					begin=true;
					value=qp[b_x+b_y*QP_W];
					//当前棋子变为选中状态
					qp[b_x+b_y*QP_W]=_XZ;
					continue;
				}
				//没有移动刚才选中的棋子，而是又选中了另个棋子
				else if(begin && ((qz==_HF &&qp[x+y*QP_W]<0) ||(qz==_LF &&qp[x1+y1*QP_W]>0)) )
				{
					//还原上个棋子
					qp[b_x+b_y*QP_W]=value;
					if(qz==_HF)
					{
						b_x=x;
						b_y=y;
					}
					else
					{
						b_x=x1;
						b_y=y1;
					}
					//记录现在选中的棋子
					value=qp[b_x+b_y*QP_W];
					qp[b_x+b_y*QP_W]=_XZ;
					continue;
				}
				//选中棋子后，要移动的位置判断
				//移动棋子要不吃掉对方棋子，要不移动到没有棋子的地方
				else if(begin && ((qz==_HF &&qp[x+y*QP_W]>=0) ||(qz==_LF &&qp[x1+y1*QP_W]<=0)) )
				{
					if(qz==_HF)
					{
						e_x=x;
						e_y=y;
					}
					else
					{
						e_x=x1;
						e_y=y1;
					}
					//得到棋盘各元素的下子规则函数进行下子判断
					//选中棋子到移动棋子都成功后，又进行下次选棋子的判断，begin变为false
					if(value ==L_JU ||value==H_JU)	
					{
						if(ju(b_x,b_y,e_x,e_y))
						{
							qp[e_x+QP_W*e_y]=value;
							qp[b_x+QP_W*b_y]=0;
							begin=false;
						}
						else
						{
							qp[b_x+QP_W*b_y]=value;
							begin=false;
						};
					}
					if(value ==L_PAO ||value==H_PAO)	
					{
						if(pao(b_x,b_y,e_x,e_y))
						{
							qp[e_x+QP_W*e_y]=value;
							qp[b_x+QP_W*b_y]=0;
							begin=false;
						}
						else
						{
							qp[b_x+QP_W*b_y]=value;
							begin=false;
						};
					}
					if(value ==L_MA ||value==H_MA)	
					{
						if(ma(b_x,b_y,e_x,e_y))
						{
							qp[e_x+QP_W*e_y]=value;
							qp[b_x+QP_W*b_y]=0;
							begin=false;
						}
						else
						{
							qp[b_x+QP_W*b_y]=value;
							begin=false;
						};
					}
					if(value ==L_SHI ||value==H_SHI)	
					{
						if(shi(b_x,b_y,e_x,e_y))
						{
							qp[e_x+QP_W*e_y]=value;
							qp[b_x+QP_W*b_y]=0;
							begin=false;
						}
						else
						{
							qp[b_x+QP_W*b_y]=value;
							begin=false;
						};
					}
					if(value ==L_XIANG ||value==H_XIANG)	
					{
						if(xiang(b_x,b_y,e_x,e_y))
						{
							qp[e_x+QP_W*e_y]=value;
							qp[b_x+QP_W*b_y]=0;
							begin=false;
						}
						else
						{
							qp[b_x+QP_W*b_y]=value;
							begin=false;
						};
					}
					if(value ==L_JIANG ||value==H_SHUAI)	
					{
						if(wang(b_x,b_y,e_x,e_y))
						{
							qp[e_x+QP_W*e_y]=value;
							qp[b_x+QP_W*b_y]=0;
							begin=false;
						}
						else
						{
							qp[b_x+QP_W*b_y]=value;
							begin=false;
						};
					}
					if(value ==L_BING ||value==H_BING)	
					{
						if(bing(b_x,b_y,e_x,e_y))
						{
							qp[e_x+QP_W*e_y]=value;
							qp[b_x+QP_W*b_y]=0;
							begin=false;
						}
						else
						{
							qp[b_x+QP_W*b_y]=value;
							begin=false;
						};
					}
					if(qp[b_x+QP_W*b_y]==0)
						qz=(qz==_HF?_LF:_HF);
				}
				//胜负判断
				int n_JIANG=0;
				int n_SHUAI=0;
				for(int i=0;i<QP_S;++i)
				{
					if(qp[i]==L_JIANG)
						n_JIANG++;
					if(qp[i]==H_SHUAI)
						n_SHUAI++;
				}
				if(n_JIANG==0)
				{
					cout<<"红方胜利!";
					cout<<"退出游戏请按y或Y，"<<endl;
					char sel=_getch();
					if(sel=='Y' || sel=='y')
						break;
				}
				if(n_SHUAI==0)
				{
					cout<<"蓝方胜利!";
					cout<<"退出游戏请按y或Y，"<<endl;
					char sel=_getch();
					if(sel=='Y' || sel=='y')
						break;
				}
			}
		}
	}
	system("pause");
}