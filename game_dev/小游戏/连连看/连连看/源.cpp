#include<iostream>
#include <conio.h>
#include <time.h>
#include <Windows.h>
using namespace std;
#include<vector>
#include "LLK.h"
void main()
{
	cout<<"即将开始连连看，";
	system("pause");
	//获取控制台颜色指针
	HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);
	int x=1,y=1;
	int map[MAP_S]={};
	//获取两个图案之间的路径
	int path[MAP_S];
	//选中第一个图案的标志
	bool begin=false;
	//记录第一个图案的坐标
	int record_begin;
	//记录要配对的图案的坐标
	int record_end;
	int defen=0;
	//记录消除的图案个数
	int gs=0;
	int GameState=0;
	srand((unsigned int)time(0));
	while(1)
	{
		//初始化游戏
		if(GameState ==0)
		{
			map[0]=_ZA;
			map[MAP_W-1]=_ZA;
			map[MAP_S-1]=_ZA;
			map[MAP_S-MAP_W]=_ZA;
			//初始化各个图案的个数
			int gs=0;
			while(gs<(MAP_W-2)*(MAP_W-2)/5)
			{
				int n=rand()%(MAP_S);
				if(map[n]==0 && n/MAP_W!=0 && n/MAP_W!=MAP_H-1 && n%MAP_W!=0 && n%MAP_W!=MAP_W-1)
				{
					map[n]=_XX;
					gs++;
				}
				else
					continue;
			}
			gs=0;
			while(gs<(MAP_W-2)*(MAP_W-2)/5)
			{
				int n=rand()%(MAP_S);
				if(map[n]==0 && n/MAP_W!=0 && n/MAP_W!=MAP_H-1 && n%MAP_W!=0 && n%MAP_W!=MAP_W-1)
				{
					map[n]=_YX;
					gs++;
				}
				else
					continue;
			}
			gs=0;
			while(gs<(MAP_W-2)*(MAP_W-2)/5)
			{
				int n=rand()%(MAP_S);
				if(map[n]==0 && n/MAP_W!=0 && n/MAP_W!=MAP_H-1 && n%MAP_W!=0 && n%MAP_W!=MAP_W-1)
				{
					map[n]=_LX;
					gs++;
				}
				else
					continue;
			}
			gs=0;
			while(gs<(MAP_W-2)*(MAP_W-2)/5)
			{
				int n=rand()%(MAP_S);
				if(map[n]==0 && n/MAP_W!=0 && n/MAP_W!=MAP_H-1 && n%MAP_W!=0 && n%MAP_W!=MAP_W-1)
				{
					map[n]=_FK;
					gs++;
				}
				else
					continue;
			}
			gs=0;
			while(gs<(MAP_W-2)*(MAP_W-2)/5)
			{
				int n=rand()%(MAP_S);
				if(map[n]==0 && n/MAP_W!=0 && n/MAP_W!=MAP_H-1 && n%MAP_W!=0 && n%MAP_W!=MAP_W-1)
				{
					map[n]=_SJ;
					gs++;
				}
				else
					continue;
			}
			for(int i=0;i<MAP_S;++i)
			{
				if(map[i]==0)
					map[i]=_TL;
			}
			GameState=1;
		}
		else
		{
			system("cls");
			SetConsoleTextAttribute(h, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
			cout<<"------- 连连看--------"<<endl;
			cout<<"-------操作说明-------"<<endl;
			cout<<"按键说明--W:上   A:左   S:下   D:右 "<<endl;
			cout<<"Space：选中图案  N:退出"<<endl<<endl;
			//☆★○●◇◆□■△▲
			for(int i=0;i<MAP_S;++i)
			{
				//得到各个图案的颜色
				if(map[i]==_XX || map[i]==S_XX)
					SetConsoleTextAttribute(h,FOREGROUND_GREEN);
				else if(map[i]==_LX || map[i]==S_LX)
					SetConsoleTextAttribute(h,FOREGROUND_RED);
				else if(map[i]==_YX || map[i]==S_YX)
					SetConsoleTextAttribute(h,FOREGROUND_BLUE);
				else if(map[i]==_FK || map[i]==S_FK)
					SetConsoleTextAttribute(h,FOREGROUND_RED | FOREGROUND_BLUE);
				else if(map[i]==_SJ || map[i]==S_SJ)
					SetConsoleTextAttribute(h,FOREGROUND_RED | FOREGROUND_GREEN);
				if(i==x+y*MAP_W)
				{
					SetConsoleTextAttribute(h, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
					cout<<"看";
				}
				else
				{
					switch (map[i])
					{
					case _LJ:cout<<"→";break;
					case _TL:cout<<"  ";break;
					case _ZA:cout<<"  ";break;
					case _XX:cout<<"★";break;
					case _YX:cout<<"●";break;
					case _LX:cout<<"◆";break;
					case _FK:cout<<"■";break;
					case _SJ:cout<<"▲";break;
					case S_XX:cout<<"☆";break;
					case S_YX:cout<<"○";break;
					case S_LX:cout<<"◇";break;
					case S_FK:cout<<"□";break;
					case S_SJ:cout<<"△";break;
					}
				}
				if(i%MAP_W == MAP_W-1)
					cout<<endl;
			}
			SetConsoleTextAttribute(h, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
			cout<<"       得分： "<<defen<<endl;
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
			if((input == 'W' || input =='w') && y>1)
				y--;
			if((input == 'S' || input =='s') && y<MAP_H-2)
				y++;
			if((input == 'A' || input =='a') && x>1)
				x--;
			if((input == 'D' || input =='d') && x<MAP_W-2)
				x++;
			if(input == ' ' && map[x+MAP_W*y]!=_TL && map[x+MAP_W*y]!=_ZA)
			{
				//选中第一个图案
				if(!begin)
				{
					switch (map[x+y*MAP_W])
					{
					case _XX:map[x+y*MAP_W]=S_XX;break;
					case _YX:map[x+y*MAP_W]=S_YX;break;
					case _LX:map[x+y*MAP_W]=S_LX;break;
					case _FK:map[x+y*MAP_W]=S_FK;break;
					case _SJ:map[x+y*MAP_W]=S_SJ;break;
					}
					record_begin=x+y*MAP_W;
					begin=true;
					continue;
				}
				//选中要配对的图案
				if(begin)
				{
					record_end=x+y*MAP_W;
					int r=CLLK::FindPath(map,MAP_W,MAP_H,record_begin,record_end,path);
					switch (map[record_end])
					{
					case _XX:map[record_end]=S_XX;break;
					case _YX:map[record_end]=S_YX;break;
					case _LX:map[record_end]=S_LX;break;
					case _FK:map[record_end]=S_FK;break;
					case _SJ:map[record_end]=S_SJ;break;
					}
					//两个图案之间有通路，并且两个图案相同，配对成功
					if(map[record_end]==map[record_begin] && r>1 && record_begin!=record_end)
					{
						map[record_end]=_TL;
						map[record_begin]=_TL;
						defen++;
						gs+=2;
						begin=false;
					}
					//配对不成功
					else
					{
						switch (map[record_begin])
						{
						case S_XX:map[record_begin]=_XX;break;
						case S_YX:map[record_begin]=_YX;break;
						case S_LX:map[record_begin]=_LX;break;
						case S_FK:map[record_begin]=_FK;break;
						case S_SJ:map[record_begin]=_SJ;break;
						}
						begin=true;
						switch (map[record_end])
						{
						case _XX:map[record_end]=S_XX;break;
						case _YX:map[record_end]=S_YX;break;
						case _LX:map[record_end]=S_LX;break;
						case _FK:map[record_end]=S_FK;break;
						case _SJ:map[record_end]=S_SJ;break;
						}
						record_begin=record_end;
					}
				}
			}
			if(gs==100)
			{
				cout<<"游戏通关，按y或Y继续，退出请按任意键"<<endl;
				char sel=_getch();
				if((input == 'Y' || input =='y'))
					GameState=0;
				else
					break;
			}
		}//GameState括号
	}//while括号
	system("pause");
}
