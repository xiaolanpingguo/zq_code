#ifndef _RENDER_H_
#define _RENDER_H_

class CRender
{
	int m_iW;
	int m_iH;
	char* m_pMap;
public:
	CRender(); 
	~CRender();

	//销毁渲染器
	void DestroyRender();
	//void RelaseRender

	//创建渲染器
	void CreateRender(int w,int h); 

	//清空渲染器
	void ClearRender();

	//设置渲染器-切换关卡，运行地图发生改变时调用
	bool SetRender(int x,int y,const char* c);

	//返回渲染器，外部可以调用，主要用于打印
	char* GetRender();
};

#endif