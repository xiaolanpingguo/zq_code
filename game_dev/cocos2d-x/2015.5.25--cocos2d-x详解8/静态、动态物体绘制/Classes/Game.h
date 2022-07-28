#ifndef __GAME_H__
#define __GAME_H__

#include "GameLayer.h"
#include <list>

#define _MAP_W 64 //地图的逻辑宽
#define _MAP_H 64 //地图的逻辑高
#define _MAP_S (_MAP_W * _MAP_H) //地图的逻辑大小

//动态物体管理
class DynamicElementManager
{
public:
	int m_MapW, m_MapH; //地图的像素宽、像素高
	int m_AreaW, m_AreaH; //区域的像素宽、像素高
	int m_AreaXNum, m_AreaYNum, m_AreaNum; //区域的X方向数量、Y方向数量、总数
	std::list<CCRect> m_Elements; //所有物体
	std::list<CCRect*>* m_AreaList; //区域表

	//根据矩形得到该矩形跨越的区域
	int GetArea(CCRect* r, int* a);

	//构造
	DynamicElementManager(
		int MapW, int MapH,
		int AreaXNum, int AreaYNum);

	//析构
	~DynamicElementManager();

	//创建物体
	CCRect* CreateDE(const CCRect& r);

	//删除物体
	bool DeleteDE(CCRect* e);

	//移动物体
	bool MoveDE(CCRect* e, int mx, int my);

	//得到绘制物体
	void GetRenderDE(
		const CCRect& view,
		std::list<CCRect*>* m_RenderDEList);
};

class CGame : public CGameLayer
{
	CCTexture2D* t0;
	CCTexture2D* t1;
	char map[_MAP_S];
	int x, y; //英雄在大地图上面的坐标

public:

	CGame();

	//virtual void Enter();
	//virtual void InputDown(CCPoint* p);
	//virtual void InputMove(CCPoint* p, int n);
	virtual void InputUp(CCPoint* p);
	virtual void Output();
	virtual void Logic(float dt);
	//virtual void Exit();
	void OnUIMessage(int id, int msg);
};

#endif