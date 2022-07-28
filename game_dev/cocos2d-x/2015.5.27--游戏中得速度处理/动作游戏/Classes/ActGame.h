#ifndef _ACT_GAME_H_
#define _ACT_GAME_H_

#include <list>

//矩形结构体
struct _RECTANGLE
{
	int x1, y1; //左上角x、y坐标
	int x2, y2; //右下角x、y坐标
};

//矩形碰撞
bool RectCollide(const _RECTANGLE* r1,
				 const _RECTANGLE* r2,
				 _RECTANGLE* r3);

//物体结构体
struct _OBJECT
{
	_RECTANGLE r;
	int csx, csy;
	int ksx, ksy;
	int asx, asy;
};

class CActGame
{
	int m_MapLW, m_MapLH; //地图逻辑宽、高
	int m_MapPW, m_MapPH; //地图像素宽、高
	int m_GridW, m_GridH; //格子的像素宽、高
	char* m_Map; //凡是小于等于0的数据都是障碍格子

	std::list<_OBJECT> m_ObjList; //物体表

public:

	//本类可以加上拷贝构造和同类赋值的

	//构造
	CActGame(
		int MapLW, int MapLH,
		int GridW, int GridH);

	//析构
	~CActGame();

	//设置地图
	bool SetMap(int x, int y, char d);

	//得到地图
	char* GetMap(int x, int y);

	//创建物体
	_OBJECT* CreateObject(
		_RECTANGLE* r, //物体矩形
		int csx = 0, int csy = 0, //瞬时速度（current speed）
		int ksx = 0, int ksy = 0, //持续速度（keep speed）
		int asx = 0, int asy = 0); //加速度（accelerate speed）

	//移动物体
	bool MoveObject(
		_OBJECT* obj,
		int st, //速度类型：012分别代表瞬时速度、持续速度、加速度
		int sx, int sy); //速度数据

	//删除物体
	bool EraseObject(_OBJECT* obj);

	//运行
	void Run();
};

#endif