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

	DynamicElementManager dem;
	struct _MONSTER
	{
		CCRect* id; //物体地址
		int dir; //移动方向0123代表上下左右
		int move; //移动次数
	};
	std::list<_MONSTER> m_Monster; //怪物表

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

//struct _RECTANGLE
//{
//	int x1, y1, x2, y2;
//};
//
//bool RectCollide(const _RECTANGLE* r1,
//				 const _RECTANGLE* r2,
//				 _RECTANGLE* r3)
//{
//	if (r1->x1 > r2->x2 ||
//		r2->x1 > r1->x2 ||
//		r1->y1 > r2->y2 ||
//		r2->y1 > r1->y2)
//		return false;
//	else
//	{
//		*r3 = *r1;
//		if (r2->x1 > r1->x1)
//			r3->x1 = r2->x1;
//		if (r2->x2 < r1->x2)
//			r3->x2 = r2->x2;
//		if (r2->y1 > r1->y1)
//			r3->y1 = r2->y1;
//		if (r2->y2 < r1->y2)
//			r3->y2 = r2->y2;
//		return true;
//	}
//}

//在处理游戏中的碰撞检测时，也可以使用上述的区域划分法，一般
//来说碰撞检测的区域应该比可见性检查还要小，一个物体移动之后
//是可以根据其矩形判断出来它在哪个（哪两个？哪四个）区域，然
//后检测的时候就只需要和其所在的区域里面的所有物体进行碰撞检
//测即可，不在其所在区域的物体是不可能和这个物体发生碰撞的

#endif