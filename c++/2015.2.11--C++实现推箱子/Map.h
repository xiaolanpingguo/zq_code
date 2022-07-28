//--------------------------
//CMap类：
//记录地图的数组，主要负责地图的初始化
//(既地图关卡的切换)，游戏元素的位置发生变化的时候
//改变该对应位置的数组元素值，将地图的实时的状况给渲染
//部分
//--------------------------
#ifndef _MAP_H_
#define _MAP_H_

class CGameRole;

class CMap
{
	int m_iWidth;//地图宽
	int m_iHeight;//地图高
	
	int m_iGuanQiaZongShu;//关卡总数
	int m_iDangQianGuanQia;//当前关卡

	int m_iMapSLength;//地图的总大小
	int m_iMapELength;//每个关卡的地图大小
	char* m_pMapSum;//总地图的堆数组
	char* m_pMap;//每个关卡的地图数组
	CGameRole* m_pRole;//游戏元素数组
public:

	~CMap();

	void Release();

	//在读取地图的时候调用，以创建存储地图的内存空间
	void InitMap(int gqzs,int zditudaxiao,char* pmap,int w,int h);

	//在读取关卡地图的时候使用-读取存档调用
	void LoadMap(int dqgq,char* pdqmap);

	//获取总地图数组的地址
	char* GetMapSum();

	//获取当前关卡的地图数组
	char* GetMap();

	//设置当前关卡的地图
	void SetGuanQiaMap();

	//设置当前关卡
	void SetGuanQia(int guanqia);

	//获取当前关卡
	int GetGuanQia();

	//设置游戏地图元素-逻辑中调用
	bool SetMapData(int x,int y,char c);
	
	int GetWidth();

	int GetHeight();

	int GetMapDaXiao();
};

#endif