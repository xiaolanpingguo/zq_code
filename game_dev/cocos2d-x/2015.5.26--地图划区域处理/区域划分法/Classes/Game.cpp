#include "Game.h"
#include "Button.h"
#include "AppDelegate.h"
#include <assert.h>

#define _VIEW_W _DEBUG_W //视口宽
#define _VIEW_H _DEBUG_H //视口高
#define _GRID_W 40 //格子的像素宽
#define _GRID_H 30 //格子的像素高
#define _DB_W 50 //方向按钮宽
#define _DB_H 50 //方向按钮高
#define _INPUT_U 1 //输入上
#define _INPUT_D 2 //输入下
#define _INPUT_L 3 //输入左
#define _INPUT_R 4 //输入右
#define _HERO_SPEED 10 //英雄速度
#define _HERO_W _GRID_W //英雄的像素宽
#define _HERO_H _GRID_H //英雄的像素高

int DynamicElementManager::GetArea(CCRect* r, int* a)
{
	int x2 = r->origin.x + r->size.width - 1;
	int y2 = r->origin.y + r->size.height - 1;

	int left = r->origin.x / m_AreaW;
	int top = r->origin.y / m_AreaH;
	int right = x2 / m_AreaW;
	int bottom = y2 / m_AreaH;

	int result = 0;

	//左右区域一致
	if (left == right)
	{
		//上下区域一致
		if (top == bottom)
		{
			//物体只在一个区域中
			a[result++] = left + top * m_AreaXNum;
		}
		//下区域大于上区域
		else
		{
			//物体在上下两个区域中
			a[result++] = left + top * m_AreaXNum;
			a[result++] = left + bottom * m_AreaXNum;
		}
	}
	//右区域大于左区域
	else
	{
		//上下区域一致
		if (top == bottom)
		{
			//物体在左右两个区域中
			a[result++] = left + top * m_AreaXNum;
			a[result++] = right + top * m_AreaXNum;
		}
		//下区域大于上区域
		else
		{
			//物体在上下左右四个区域中
			a[result++] = left + top * m_AreaXNum;
			a[result++] = right + top * m_AreaXNum;
			a[result++] = left + bottom * m_AreaXNum;
			a[result++] = right + bottom * m_AreaXNum;
		}
	}

	return result;
}

DynamicElementManager::DynamicElementManager(
	int MapW, int MapH,
	int AreaXNum, int AreaYNum)
{
	assert(MapW % AreaXNum == 0 && MapH % AreaYNum == 0);

	m_MapW = MapW;
	m_MapH = MapH;
	m_AreaXNum = AreaXNum;
	m_AreaYNum = AreaYNum;
	m_AreaNum = m_AreaXNum * m_AreaYNum;
	m_AreaW = m_MapW / m_AreaXNum;
	m_AreaH = m_MapH / m_AreaYNum;

	//创建区域表
	m_AreaList = new std::list<CCRect*>[m_AreaNum];
}

DynamicElementManager::~DynamicElementManager()
{
	delete [] m_AreaList;
}

CCRect* DynamicElementManager::CreateDE(const CCRect& r)
{
	//创建物体到物体表中
	m_Elements.push_back(r);

	//得到物体地址
	CCRect* p = &(m_Elements.back());

	//根据物体位置计算其所在区域
	int a[4];
	int n = GetArea(p, a);

	//将物体信息放入区域
	for (int i = 0; i < n; ++i)
		m_AreaList[a[i]].push_back(p);

	return p;
}

bool DynamicElementManager::DeleteDE(CCRect* e)
{
	//删除区域表中的物体信息
	int a[4];
	int n = GetArea(e, a);
	for (int i = 0; i < n; ++i)
	{
		for (std::list<CCRect*>::iterator it = m_AreaList[a[i]].begin(); it != m_AreaList[a[i]].end(); ++it)
		{
			if (e == *it)
			{
				m_AreaList[a[i]].erase(it);
				break;
			}
		}
	}

	//删除物体表中的物体信息
	for (std::list<CCRect>::iterator it = m_Elements.begin(); it != m_Elements.end(); ++it)
	{
		if (&(*it) == e)
			m_Elements.erase(it);
	}

	return true;
}

bool DynamicElementManager::MoveDE(CCRect* e, int mx, int my)
{
	//得到移动前、移动后物体所在区域
	int a1[4], a2[4];
	int n1 = GetArea(e, a1);
	CCRect e2(e->origin.x + mx, e->origin.y + my, e->size.width, e->size.height);
	int n2 = GetArea(&e2, a2);

	//更新位置
	e->origin.x += mx;
	e->origin.y += my;

	//从移动前区域表中删除物体
	for (int i = 0; i < n1; ++i)
	{
		for (std::list<CCRect*>::iterator it = m_AreaList[a1[i]].begin(); it != m_AreaList[a1[i]].end(); ++it)
		{
			if (e == (*it))
			{
				m_AreaList[a1[i]].erase(it);
				break;
			}
		}
	}

	//将物体插入到当前的区域表中
	for (int i = 0; i < n2; ++i)
		m_AreaList[a2[i]].push_back(e);

	//可以通过讨论具体的位移结果来确定新的区域，这样的话
	//可以在某种层度上加快我们的处理，避免了从物体原来所
	//在区域表删除，重新加入到新的区域表中
	//1个区域
	//2个区域：（左，右）、（上，下）
	//4个区域：（左上，右上，左下，右下）
	//右移
	//if (mx > 0)
	//{
	//	switch (n1)
	//	{
	//	case 1:
	//		{
	//			switch (n2)
	//			{
	//			case 1:
	//				{
	//					break;
	//				}
	//			case 2:
	//				{
	//					break;
	//				}
	//			}
	//			break;
	//		}
	//	case 2:
	//		{
	//			break;
	//		}
	//	case 4:
	//		{
	//			break;
	//		}
	//	}
	//}
	////左移
	//else if (mx < 0)
	//{
	//
	//}
	////横方向没有变化
	//else
	//{
	//
	//}

	return true;
}

void DynamicElementManager::GetRenderDE(const CCRect& view,
										std::list<CCRect*>* m_RenderDEList)
{
	m_RenderDEList->clear();

	//得到视口所占据的区域
	int x1 = view.origin.x / m_AreaW;
	int y1 = view.origin.y / m_AreaH;
	int x2 = (view.origin.x + view.size.width - 1) / m_AreaW;
	int y2 = (view.origin.y + view.size.height - 1) / m_AreaH;

	//定义辅助的集合
	//std::set<CCRect*> s;

	//得到所有物体
	for (int y = y1; y <= y2; ++y)
	{
		for (int x = x1; x <= x2; ++x)
		{
			int i = x + y * m_AreaXNum;

			//得到里面的所有物体放入到待渲染表中
			for (std::list<CCRect*>::iterator it = m_AreaList[i].begin(); it != m_AreaList[i].end(); ++it)
			{
				//if (s.find(*it) == s.end())
				//{
					m_RenderDEList->push_back(*it);
				//	s.insert(*it);
				//}
			}
		}
	}
}

#define _MONSTER_NUM 5000
#define _MONSTER_W 60
#define _MONSTER_H 60
#define _MONSTER_SPEED 10
#define _MONSTER_MOVE 10

CGame::CGame()
:
dem(_MAP_W * _GRID_W, _MAP_H * _GRID_H, 4, 4)
{
	//背景
	t0 = CCTextureCache::sharedTextureCache()->addImage("Game/00.PNG");

	//英雄
	t1 = CCTextureCache::sharedTextureCache()->addImage("Game/01.PNG");

	//1234分别代表按钮上下左右
	LoadUI(_INPUT_U, new CButton(CCRect(50, _VIEW_H - 150, _DB_W, _DB_H), "Game/Dir/d_i.PNG", "Game/Dir/d_n.PNG", "Game/Dir/d_d.PNG"));
	LoadUI(_INPUT_D, new CButton(CCRect(50, _VIEW_H - 50, _DB_W, _DB_H), "Game/Dir/d_i.PNG", "Game/Dir/d_n.PNG", "Game/Dir/d_d.PNG"));
	LoadUI(_INPUT_L, new CButton(CCRect(0, _VIEW_H - 100, _DB_W, _DB_H), "Game/Dir/d_i.PNG", "Game/Dir/d_n.PNG", "Game/Dir/d_d.PNG"));
	LoadUI(_INPUT_R, new CButton(CCRect(100, _VIEW_H - 100, _DB_W, _DB_H), "Game/Dir/d_i.PNG", "Game/Dir/d_n.PNG", "Game/Dir/d_d.PNG"));

	//得到游戏地图
	_FILE_DATA fd = GetResourceFileData("Game/game.txt");
	for (int i = 0, j = 0; i < fd.fs; ++i)
	{
		if (fd.fd[i] >= '0' && fd.fd[i] <= '9')
			map[j++] = fd.fd[i] - '0';
	}
	delete [] fd.fd;

	//初始化英雄
	x = 0;
	y = 0;

	//创建怪物
	srand(100);
	for (int i = 0; i < _MONSTER_NUM; ++i)
	{
		int x = rand() % (_MAP_W * _GRID_W - _MONSTER_W);
		int y = rand() % (_MAP_H * _GRID_H - _MONSTER_H);
		CCRect* p = dem.CreateDE(CCRect(x, y, _MONSTER_W, _MONSTER_H));
		_MONSTER m = {p, -1, 0};
		m_Monster.push_back(m);
	}
}

void CGame::InputUp(CCPoint* p)
{
	
}

void CGame::Logic(float dt)
{
	//Beep(500, 20);

	//怪物移动
	for (std::list<_MONSTER>::iterator it = m_Monster.begin(); it != m_Monster.end(); ++it)
	{
		if (it->move > 0)
		{
			//判断本次移动是否超出边界
			CCRect r = *it->id;
			switch (it->dir)
			{
			case 0: r.origin.y -= _MONSTER_SPEED; break;
			case 1: r.origin.y += _MONSTER_SPEED; break;
			case 2: r.origin.x -= _MONSTER_SPEED; break;
			case 3: r.origin.x += _MONSTER_SPEED; break;
			}
			bool in =
				r.origin.x > 0 &&
				(r.origin.x + r.size.width - 1) < (_MAP_W * _GRID_W) &&
				r.origin.y > 0 &&
				(r.origin.y + r.size.height - 1) < (_MAP_H * _GRID_H);
			if (in)
			{
				dem.MoveDE(it->id, r.origin.x - it->id->origin.x, r.origin.y - it->id->origin.y);
				it->move -= 1;
			}
			else
			{
				//如果本次处理要越界那么设置不进行移动了
				it->move = 0;
			}
		}
	}

#ifdef _WIN32
	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		if (y > 0)
			y -= _HERO_SPEED;
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		if (y < _MAP_H * _GRID_H - _HERO_H)
			y += _HERO_SPEED;
	}
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		if (x > 0)
			x -= _HERO_SPEED;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		if (x < _MAP_W * _GRID_W - _HERO_W)
			x += _HERO_SPEED;
	}
	if (GetAsyncKeyState(VK_SPACE) & 1)
	{
		for (std::list<_MONSTER>::iterator it = m_Monster.begin(); it != m_Monster.end(); ++it)
		{
			if (rand() % _MONSTER_MOVE == 0)
			{
				if (it->move == 0)
				{
					//随机方向
					it->dir = rand() % 4;

					//随机移动值
					it->move = rand() % 101 + 100;
				}
			}
		}
	}
#endif
}

void CGame::Output()
{
	//根据英雄位置计算视口位置
	int vx, vy;
	if (x <= (_VIEW_W - _HERO_W) / 2)
		vx = 0;
	else if (x > (_GRID_W * _MAP_W) - (_VIEW_W + _HERO_W) / 2)
		vx = (_GRID_W * _MAP_W) - _VIEW_W;
	else
		vx = x - (_VIEW_W - _HERO_W) / 2;
	if (y <= (_VIEW_H - _HERO_H) / 2)
		vy = 0;
	else if (y > (_GRID_H * _MAP_H) - (_VIEW_H + _HERO_H) / 2)
		vy = (_GRID_H * _MAP_H) - _VIEW_H;
	else
		vy = y - (_VIEW_H - _HERO_H) / 2;

	//绘制地图方法1：效率太低，绘制了很多根本看不见的地图格子
	//for (int cy = 0; cy < _MAP_H; ++cy)
	//{
	//	for (int cx = 0; cx < _MAP_W; ++cx)
	//	{
	//		DrawImage1(
	//			t0,
	//			map[cx + cy * _MAP_W] * _GRID_W, 0, _GRID_W, _GRID_H,
	//			cx * _GRID_W - vx, cy * _GRID_H - vy, _GRID_W, _GRID_H);
	//	}
	//}

	//绘制地图方法2：通过计算视口范围之内的格子来确定静态物体的绘制
	int x1 = vx / _GRID_W;
	int y1 = vy / _GRID_H;
	int x2 = (vx + _VIEW_W - 1) / _GRID_W;
	int y2 = (vy + _VIEW_H - 1) / _GRID_H;
	int offsetx = vx % _GRID_W;
	int offsety = vy % _GRID_H;
	for (int cy = y1; cy <= y2; ++cy)
	{
		for (int cx = x1; cx <= x2; ++cx)
		{
			DrawImage1(
				t0,
				map[cx + cy * _MAP_W] * _GRID_W, 0, _GRID_W, _GRID_H,
				(cx - x1) * _GRID_W - offsetx,
				(cy - y1) * _GRID_H - offsety,
				_GRID_W,
				_GRID_H);
		}
	}

	//绘制怪物1
	//int b = GetTickCount();
	//for (std::list<_MONSTER>::iterator it = m_Monster.begin(); it != m_Monster.end(); ++it)
	//{
	//	CCPoint p1 = ccp(it->id->origin.x - vx, it->id->origin.y - vy);
	//	CCPoint p2 = ccp(p1.x + it->id->size.width - 1, p1.y + it->id->size.height - 1);
	//	DrawRect2(p1, p2, 0xff0000ff);
	//}
	//char buf[32];
	//sprintf_s(buf, 32, "%d\n", GetTickCount() - b);
	//OutputDebugStringA(buf);

	//绘制怪物2
	int b = GetTickCount();
	std::list<CCRect*> rl;
	dem.GetRenderDE(CCRect(vx, vy, _VIEW_W, _VIEW_H), &rl);
	for (std::list<CCRect*>::iterator it = rl.begin(); it != rl.end(); ++it)
	{
		CCPoint p1 = ccp((*it)->origin.x - vx, (*it)->origin.y - vy);
		CCPoint p2 = ccp(p1.x + (*it)->size.width - 1, p1.y + (*it)->size.height - 1);
		DrawRect2(p1, p2, 0xff0000ff);
	}
	char buf[32];
	sprintf_s(buf, 32, "%d\n", GetTickCount() - b);
	OutputDebugStringA(buf);

	//绘制英雄
	DrawImage1(
		t1,
		0, 0, _HERO_W, _HERO_H,
		x - vx, y - vy, _HERO_W, _HERO_H);
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