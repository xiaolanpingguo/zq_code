#include"GameInput.h"
#include"mplane.h"
#include<windows.h>
#include"mplane.h"
#include<vector>
#include"GameLogic.h"
#include"mBullet.h"
#include"eBullet.h"
#include"eplane.h"
extern CMplane g_mplane;
extern std::vector<CMbullet> g_vMbullet;
extern std::vector<CEbullet> g_vEbullet;
extern std::vector<CEplane> g_vEplane;
extern CGameLogic gameLogic;
void CGameInput::run(HWND hwnd)
{
	POINT p;
	GetCursorPos(&p);
	ScreenToClient(hwnd, &p);
	if(p.x<0)
		p.x = 0 ;
	RECT r;
	GetClientRect(hwnd,&r);
	if(p.x>r.right-60)
		p.x=r.right-60;
	if(p.y<0)
		p.y =0;
	if(p.y>r.bottom-60)
		p.y = r.bottom-60;
	g_mplane.run(p.x,p.y);
}

void CGameInput::addMbullet()
{
	CMbullet mb(g_mplane.GetX(),g_mplane.GetY());
	g_vMbullet.push_back(mb);
}

void CGameInput::boom()
{
	gameLogic.setScore(gameLogic.getScore()+g_vEplane.size());
	g_vEplane.clear();
	g_vMbullet.clear();
	g_vEbullet.clear();
}