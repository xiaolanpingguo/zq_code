#include"GameOutput.h"
#include "eplane.h"
#include<vector>
#include"mBullet.h"
#include"eBullet.h"
#include"GameLogic.h"
#include"mplane.h"
extern std::vector<CEplane> g_vEplane;
extern std::vector<CMbullet> g_vMbullet;
extern std::vector<CEbullet> g_vEbullet;
extern CMplane g_mplane;
extern CGameLogic gameLogic;


void CGameOutput::pm(HWND hwnd)
{
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hwnd,&ps);
	char buf[256];
	switch(gameLogic.getSpeed())
	{
	case SLOW:
		sprintf_s(buf,256,"游戏速度:慢 体力:%d 得分:%d",gameLogic.getHp(),gameLogic.getScore());
		break;
	case MID:
		sprintf_s(buf,256,"游戏速度:中 体力:%d 得分:%d",gameLogic.getHp(),gameLogic.getScore());
		break;
	case QUICK:
		sprintf_s(buf,256,"游戏速度:快 体力:%d 得分:%d",gameLogic.getHp(),gameLogic.getScore());
		break;
	}
	
	TextOutA(hdc,0,0,buf,256);
	//绘制敌方飞机
	for(std::vector<CEplane>::iterator i=g_vEplane.begin();i!=g_vEplane.end();i++)
	{
		int x=i->GetX();
		int y=i->GetY();
		Rectangle(hdc,x+25,y,x+75,y+20);
		Rectangle(hdc,x+40,y+20,x+60,y+80);
		Rectangle(hdc,x,y+40,x+100,y+60);
	}
	//绘制我方飞机
	Rectangle(hdc,g_mplane.GetX()+24,g_mplane.GetY(),g_mplane.GetX()+36,g_mplane.GetY()+45);
	Rectangle(hdc,g_mplane.GetX(),g_mplane.GetY()+15,g_mplane.GetX()+60,g_mplane.GetY()+30);
	Rectangle(hdc,g_mplane.GetX()+15,g_mplane.GetY()+45,g_mplane.GetX()+45,g_mplane.GetY()+60);
	//绘制我方子弹
	for(std::vector<CMbullet>::iterator i=g_vMbullet.begin();i!=g_vMbullet.end();i++)
	{
		int x =i->GetX();
		int y =i->GetY();
		Ellipse(hdc,x+25,y-10,x+35,y);
	}
	//绘制敌方子弹
	for(std::vector<CEbullet>::iterator i=g_vEbullet.begin();i!=g_vEbullet.end();i++)
	{
		int x =i->GetX();
		int y =i->GetY();
		Ellipse(hdc,x+44,y+80,x+56,y+92);
	}
	
	
	EndPaint(hwnd,&ps);
}