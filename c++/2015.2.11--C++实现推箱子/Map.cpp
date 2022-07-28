#include "Map.h"
#include <iostream>
#include "GameRole.h"
CMap::~CMap()
{
	if(m_pMap)
		delete []m_pMap;
	if(m_pMapSum)
		delete []m_pMapSum;
}

void CMap::Release()
{
	if(m_pMap)
		delete []m_pMap;
	if(m_pMapSum)
		delete []m_pMapSum;
	m_pMap = 0;
	m_pMapSum = 0;
}
/////////////////////////////////////////
//在读取地图的时候调用，以创建存储地图的内存空间
void CMap::InitMap(int gqzs,int zditudaxiao,char* pmap,int w,int h)
{
	m_iGuanQiaZongShu = gqzs;
	m_iMapSLength = zditudaxiao;
	m_pMapSum = new char[zditudaxiao];
	memcpy_s(m_pMapSum,zditudaxiao,pmap,zditudaxiao);
	m_iDangQianGuanQia = 1;
	m_iMapELength = zditudaxiao / gqzs;
	m_pMap = new char[m_iMapELength];
	m_iWidth = w;
	m_iHeight = h;
}
///////////////////////////////////
void CMap::LoadMap(int dqgq,char* pdqmap)
{
	m_iDangQianGuanQia = dqgq;
	memcpy_s(m_pMap,m_iMapELength,pdqmap,m_iMapELength);
}

//获取总地图数组的地址
char* CMap::GetMapSum()
{
	return m_pMapSum;
}

//获取当前关卡的地图数组
char* CMap::GetMap()
{
	return m_pMap;
}
////////////////////////////////////
void CMap::SetGuanQiaMap()
{
	memcpy_s(m_pMap,m_iMapELength,m_pMapSum + m_iMapELength * (m_iDangQianGuanQia - 1),m_iMapELength);
}

void CMap::SetGuanQia(int guanqia)
{
	m_iDangQianGuanQia = guanqia;
}
	
int CMap::GetGuanQia()
{
	return m_iDangQianGuanQia;
}

bool CMap::SetMapData(int x,int y,char c)
{
	if(x < 0 || x > m_iWidth - 1 || y < 0 || y > m_iHeight - 1)
		return false;
	int index = x + y *  m_iWidth;
	m_pMap[index] = c;
	return true;
}

int CMap::GetWidth()
{
	return m_iWidth;
}

int CMap::GetHeight()
{
	return m_iHeight;
}

int CMap::GetMapDaXiao()
{
	return m_iMapELength;
}
