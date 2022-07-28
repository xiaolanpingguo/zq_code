#include "Render.h"
#include <iostream>

CRender::CRender()
{}
CRender::~CRender()
{
	if(m_pMap)
		delete []m_pMap;
}

//销毁渲染器
void CRender::DestroyRender()
{
	if(m_pMap)
		delete []m_pMap;
	m_pMap = 0;
}

//创建渲染器
void CRender::CreateRender(int w,int h)
{
	m_iW = w * 2 + 1;
	m_iH = h;
	m_pMap = new char[m_iW * m_iH + 1];

	char* p = m_pMap;
	for(int i = 0; i < h;++i)
	{
		*(p += m_iW - 1) = '\n';
		p += 1;
	}
	*p = 0;
	ClearRender();
}

//清空渲染器
void CRender::ClearRender()
{
	//char* p = m_pMap;
	for(int i = 0; i < m_iH ;++i)
	{
		for(int j = 0; j < m_iW - 1;++j)
		{
			//p[j] = ' ';
			m_pMap[j + i * m_iW] = ' ';
		}
		//p += m_iW;
	}
}

//设置渲染器-切换关卡，运行地图发生改变时调用
bool CRender::SetRender(int x,int y,const char* c)
{
	if(x < 0 || x >= (m_iW - 1)/2 || y < 0 || y >= m_iH)
		return false;

	if(strlen(c) > (m_iW - 1 - 2 * x))
		return false;
	char* p = m_pMap;
	memcpy(p + y * m_iW + x * 2 ,c,strlen(c));
	return true;
}

//返回渲染器，外部可以调用，主要用于打印
char* CRender::GetRender()
{
	return m_pMap;
}