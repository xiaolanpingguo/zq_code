#include"GameLogic.h"
#include "eplane.h"
#include "mplane.h"
#include"mBullet.h"
#include"eBullet.h"
#include<vector>
#include<time.h>
#include<windows.h>
extern CGameLogic gameLogic;
extern std::vector<CEplane> g_vEplane;
extern std::vector<CMbullet> g_vMbullet;
extern std::vector<CEbullet> g_vEbullet;
extern CMplane g_mplane;

CGameLogic::CGameLogic()
{
	hp = 100;
	score = 0;
	speed = MID;
	flag=0;
}
void CGameLogic::addPlane()
{
	if(g_vEplane.size()<8)
	{
		int number;
		int p = rand()%100;
		if(p<40)
			number = 0;
		else
		if(p>=40&&p<70)
			number =1;
		else
		if(p>=70&&p<90)
			number =2;
		else
			number = 3;
		for(int i=0;i<number;i++)
		{
			CEplane pl;
			g_vEplane.push_back(pl);
		}
	}	
}

void CGameLogic::isOut(HWND hwnd)
{
	RECT r;
	GetClientRect(hwnd,&r);
	for(std::vector<CEplane>::iterator i=g_vEplane.begin();i!=g_vEplane.end();)
	{
		if(i->GetX()<=-100||i->GetX()>=r.right||i->GetY()>=r.bottom)
		{
			i = g_vEplane.erase(i);
			if(i== g_vEplane.begin())
			{
				if(g_vEplane.size()==0)
					break;
				else
					continue;
			}
		}
		if(i==g_vEplane.end())
		{
			break;
		}else
			i++;
	}
	for(std::vector<CMbullet>::iterator i=g_vMbullet.begin();i!=g_vMbullet.end();)
	{
		if(i->GetY()<=0)
		{
			i = g_vMbullet.erase(i);
			if(i== g_vMbullet.begin())
			{
				if(g_vMbullet.size()==0)
					break;
				else
					continue;
			}
		}
		if(i==g_vMbullet.end())
		{
			break;
		}else
			i++;
	}
	for(std::vector<CEbullet>::iterator i=g_vEbullet.begin();i!=g_vEbullet.end();)
	{
		if(i->GetY()>=r.bottom)
		{
			i = g_vEbullet.erase(i);
			if(i== g_vEbullet.begin())
			{
				if(g_vEbullet.size()==0)
					break;
				else
					continue;
			}
		}
		if(i==g_vEbullet.end())
		{
			break;
		}else
			i++;
	}
}

void CGameLogic::run()
{
	for(std::vector<CEplane>::iterator i=g_vEplane.begin();i!=g_vEplane.end();i++)
	{
		i->run();
	}
	for(std::vector<CMbullet>::iterator i=g_vMbullet.begin();i!=g_vMbullet.end();i++)
	{
		i->run();
	}
	for(std::vector<CEbullet>::iterator i=g_vEbullet.begin();i!=g_vEbullet.end();i++)
	{
		i->run();
	}
}

void CGameLogic::addBullet()
{
	for(std::vector<CEplane>::iterator i=g_vEplane.begin();i!=g_vEplane.end();i++)
	{
		if(rand()%15==0)
		{
			CEbullet b(i->GetX(),i->GetY());
			g_vEbullet.push_back(b);
		}
	}
}
void CGameLogic::setHp(int h)
{
	hp = h;
}
int CGameLogic::getHp()
{
	return hp;
}
void CGameLogic::setFlag(int h)
{
	flag = h;
}
int CGameLogic::getFlag()
{
	return flag;
}
void CGameLogic::setScore(int s)
{
	score = s;
}
int CGameLogic::getScore()
{
	return score;
}
void CGameLogic::setSpeed(int sp)
{
	speed = sp;
}
int CGameLogic::getSpeed()
{
	return speed;
}

void CGameLogic::isTouch()
{
	//判断我方子弹与敌方飞机的碰撞
	RECT r,r1,r2;
	std::vector<CMbullet>::iterator a=g_vMbullet.begin();
	std::vector<CEplane>::iterator b= g_vEplane.begin();
	for(int i=0;i<(int)g_vMbullet.size();i++)
	{
		r1.left=(a+i)->GetX()+25;
		r1.top =(a+i)->GetY()-10;
		r1.right=(a+i)->GetX()+35;
		r1.bottom =(a+i)->GetY();
		for(int j=0;j<(int)g_vEplane.size();j++)
		{
			r2.left =(b+j)->GetX()+25;
			r2.top =(b+j)->GetY();
			r2.right = (b+j)->GetX()+75;
			r2.bottom =(b+j)->GetY()+20;
			if(IntersectRect(&r,&r1,&r2))
			{
				g_vEplane.erase(b+j);
				j--;
				b= g_vEplane.begin();
				g_vMbullet.erase(a+i);
				a=g_vMbullet.begin();
				i--;
				gameLogic.setScore(gameLogic.getScore()+1);
				break;
			}
			r2.left =(b+j)->GetX()+40;
			r2.top =(b+j)->GetY()+20;
			r2.right = (b+j)->GetX()+60;
			r2.bottom =(b+j)->GetY()+80;
			if(IntersectRect(&r,&r1,&r2))
			{
				g_vEplane.erase(b+j);
				j--;
				b= g_vEplane.begin();
				g_vMbullet.erase(a+i);
				a=g_vMbullet.begin();
				i--;
				gameLogic.setScore(gameLogic.getScore()+1);
				break;
			}
			r2.left =(b+j)->GetX();
			r2.top =(b+j)->GetY()+40;
			r2.right = (b+j)->GetX()+100;
			r2.bottom =(b+j)->GetY()+60;
			if(IntersectRect(&r,&r1,&r2))
			{
				g_vEplane.erase(b+j);
				j--;
				b= g_vEplane.begin();
				g_vMbullet.erase(a+i);
				a=g_vMbullet.begin();
				i--;
				gameLogic.setScore(gameLogic.getScore()+1);
				break;
			}	
		}
	}
	//判断我方飞机与敌方子弹的碰撞
	std::vector<CEbullet>::iterator a1=g_vEbullet.begin();
	RECT mp_r1={g_mplane.GetX()+24,g_mplane.GetY(),g_mplane.GetX()+36,g_mplane.GetY()+45};
	RECT mp_r2={g_mplane.GetX(),g_mplane.GetY()+15,g_mplane.GetX()+60,g_mplane.GetY()+30};
	RECT mp_r3={g_mplane.GetX()+15,g_mplane.GetY()+45,g_mplane.GetX()+45,g_mplane.GetY()+60};
	for(int i=0;i<(int)g_vEbullet.size();i++)
	{
		RECT eb_r ={(a1+i)->GetX()+44,(a1+i)->GetY()+80,(a1+i)->GetX()+56,(a1+i)->GetY()+92};
		if(IntersectRect(&r,&mp_r1,&eb_r))
		{
			g_vEbullet.erase(a1+i);
			i--;
			a1= g_vEbullet.begin();
			gameLogic.setHp(gameLogic.getHp()-1);
			continue;
		}
		if(IntersectRect(&r,&mp_r2,&eb_r))
		{
			g_vEbullet.erase(a1+i);
			i--;
			a1= g_vEbullet.begin();
			gameLogic.setHp(gameLogic.getHp()-1);
			continue;
		}
		if(IntersectRect(&r,&mp_r3,&eb_r))
		{
			g_vEbullet.erase(a1+i);
			i--;
			a1= g_vEbullet.begin();
			gameLogic.setHp(gameLogic.getHp()-1);
			continue;
		}	
	}
	//敌方飞机与我方飞机碰撞
	b= g_vEplane.begin();
	for(int i=0;i<(int)g_vEplane.size();i++)
	{
		RECT ep_r1 ={(b+i)->GetX()+25,(b+i)->GetY(),(b+i)->GetX()+75,(b+i)->GetY()+20};
		RECT ep_r2 ={(b+i)->GetX()+40,(b+i)->GetY()+20,(b+i)->GetX()+60,(b+i)->GetY()+80};
		RECT ep_r3 ={(b+i)->GetX(),(b+i)->GetY()+40,(b+i)->GetX()+100,(b+i)->GetY()+60};
		if(IntersectRect(&r,&mp_r1,&ep_r1))
		{
			g_vEplane.erase(b+i);
			i--;
			b= g_vEplane.begin();
			gameLogic.setHp(gameLogic.getHp()-2);
			continue;
		}
		if(IntersectRect(&r,&mp_r1,&ep_r2))
		{
			g_vEplane.erase(b+i);
			i--;
			b= g_vEplane.begin();
			gameLogic.setHp(gameLogic.getHp()-2);
			continue;
		}
		if(IntersectRect(&r,&mp_r1,&ep_r3))
		{
			g_vEplane.erase(b+i);
			i--;
			b= g_vEplane.begin();
			gameLogic.setHp(gameLogic.getHp()-2);
			continue;
		}
		if(IntersectRect(&r,&mp_r2,&ep_r1))
		{
			g_vEplane.erase(b+i);
			i--;
			b= g_vEplane.begin();
			gameLogic.setHp(gameLogic.getHp()-2);
			continue;
		}
		if(IntersectRect(&r,&mp_r2,&ep_r2))
		{
			g_vEplane.erase(b+i);
			i--;
			b= g_vEplane.begin();
			gameLogic.setHp(gameLogic.getHp()-2);
			continue;
		}
		if(IntersectRect(&r,&mp_r2,&ep_r3))
		{
			g_vEplane.erase(b+i);
			i--;
			b= g_vEplane.begin();
			gameLogic.setHp(gameLogic.getHp()-2);
			continue;
		}
		if(IntersectRect(&r,&mp_r3,&ep_r1))
		{
			g_vEplane.erase(b+i);
			i--;
			b= g_vEplane.begin();
			gameLogic.setHp(gameLogic.getHp()-2);
			continue;
		}
		if(IntersectRect(&r,&mp_r3,&ep_r2))
		{
			g_vEplane.erase(b+i);
			i--;
			b= g_vEplane.begin();
			gameLogic.setHp(gameLogic.getHp()-2);
			continue;
		}
		if(IntersectRect(&r,&mp_r3,&ep_r3))
		{
			g_vEplane.erase(b+i);
			i--;
			b= g_vEplane.begin();
			gameLogic.setHp(gameLogic.getHp()-2);
			continue;
		}
	}
	
}



void CGameLogic::isDeath(HWND hwnd)
{
	if(gameLogic.getHp()<=0&&gameLogic.getFlag()==0)
	{
		gameLogic.setFlag(1);
		if(MessageBoxA(hwnd,"你已经挂了!\n选择是否重来\n否为退出游戏","真可惜",MB_YESNO)==IDYES)
		{
			g_vEplane.clear();
			g_vMbullet.clear();
			g_vEbullet.clear();
			gameLogic.setHp(100);
			gameLogic.setScore(0);
			gameLogic.setFlag(0);
		}else
		{
			DestroyWindow(hwnd);
		}
	}
}