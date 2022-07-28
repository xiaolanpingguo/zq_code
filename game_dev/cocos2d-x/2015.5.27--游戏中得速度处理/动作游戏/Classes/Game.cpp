#include "Game.h"
#include "Button2.h"
#include "AppDelegate.h"
#include <assert.h>

#define _MOVE_LEFT 1
#define _MOVE_RIGHT 2
#define _MOVE_JUMP 3
#define _GRID_W 40
#define _GRID_H 40
#define _GAME_W 16
#define _GAME_H 12
#define _GAME_S (_GAME_W * _GAME_H)
#define _HERO_W 30
#define _HERO_H 20

CGame::CGame()
:
ag(_GAME_W, _GAME_H, _GRID_W, _GRID_H)
{
	LoadUI(_MOVE_LEFT, new CButton2(CCRect(0, _DEBUG_H - 50, 50, 50), "Game/B/b_i.PNG", "Game/B/b_n.PNG", "Game/B/b_d.PNG"));
	LoadUI(_MOVE_RIGHT, new CButton2(CCRect(100, _DEBUG_H - 50, 50, 50), "Game/B/b_i.PNG", "Game/B/b_n.PNG", "Game/B/b_d.PNG"));
	LoadUI(_MOVE_JUMP, new CButton2(CCRect(_DEBUG_W - 50, _DEBUG_H - 50, 50, 50), "Game/B/b_i.PNG", "Game/B/b_n.PNG", "Game/B/b_d.PNG"));

	//设置障碍
	char map[] = 
	{
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0,
		1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0,
		0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1,
		0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1
	};
	for (int i = 0; i < _GAME_S; ++i)
		ag.SetMap(i % _GAME_W, i / _GAME_W, map[i]);

	//创建英雄
	_RECTANGLE r = {0, 0, _HERO_W - 1, _HERO_H - 1};
	hero = ag.CreateObject(&r);

	//设置物体加速度
	ag.MoveObject(hero, 2, 0, 1);
}

void CGame::InputUp(CCPoint* p)
{
	
}

void CGame::Logic(float dt)
{
	ag.Run();

	if (GetAsyncKeyState('A') & 0x8000)
		ag.MoveObject(hero, 0, -5, 0);
	if (GetAsyncKeyState('D') & 0x8000)
		ag.MoveObject(hero, 0, +5, 0);
	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
		ag.MoveObject(hero, 1, 0, -10);
}

void CGame::Output()
{
	DrawRect2(ccp(0, 0), ccp(_DEBUG_W, _DEBUG_H), 0x000000ff);

	//绘制地图
	for (int i = 0; i < _GAME_S; ++i)
	{
		int rx = (i % _GAME_W) * _GRID_W;
		int ry = (i / _GAME_W) * _GRID_H;
		if (*ag.GetMap(i % _GAME_W, i / _GAME_W) <= 0)
			DrawRect1(ccp(rx, ry), ccp(rx + _GRID_W, ry + _GRID_H), 0xff0000ff);
	}

	//绘制英雄
	DrawRect2(
		ccp(hero->r.x1 - _GRID_W, hero->r.y1 - _GRID_H),
		ccp(hero->r.x2 - _GRID_W, hero->r.y2 - _GRID_H),
		0x00ffffff);
}

void CGame::OnUIMessage(int id, int msg)
{
	//switch (msg)
	//{
	//	//当前层中有按钮被按下
	//case _BUTTON_CLICK:
	//	{
	//		switch (id)
	//		{
	//		case _INPUT_U:
	//			{
	//				if (y > 0)
	//					y -= _HERO_SPEED;
	//				break;
	//			}
	//		}
	//		switch (id)
	//		{
	//		case _INPUT_D:
	//			{
	//				if (y < _MAP_H * _GRID_H - _HERO_H)
	//					y += _HERO_SPEED;
	//				break;
	//			}
	//		}
	//		switch (id)
	//		{
	//		case _INPUT_L:
	//			{
	//				if (x > 0)
	//					x -= _HERO_SPEED;
	//				break;
	//			}
	//		}
	//		switch (id)
	//		{
	//		case _INPUT_R:
	//			{
	//				if (x < _MAP_W * _GRID_W - _HERO_W)
	//					x += _HERO_SPEED;
	//				break;
	//			}
	//		}
	//		break;
	//	}
	//}
}