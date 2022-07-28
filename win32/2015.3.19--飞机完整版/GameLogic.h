#ifndef _GAMELOGIC_H_
#define _GAMELOGIC_H_

#include <vector>
#include <windows.h>
//游戏逻辑类，游戏通过调用该类对象，实现对所有游戏元素的
//逻辑运行

class CPlane;
class CBullet;

class CGameLogic
{
	int m_iScore;//得分 
	std::vector<CPlane*> m_vEmenyPlane;//飞机表-敌人的
	CPlane* m_pHeroPlane;//飞机，英雄
	std::vector<CBullet*> m_vEmenyBullet;
	std::vector<CBullet*> m_vHeroBullet;
	int m_iBianJieRight;//右边界
	int m_iBianJieBottom;//下边界
public:
	CGameLogic();
	~CGameLogic();

	//初始化：分数，边界
	void Init(int score,int bianjr,int bianjb);

	//运行
	void Run();

	//设置英雄位置
	void SetHeroPoint(POINT point);

	//设置英雄攻击
	void SetHeroAttack(POINT point);

	//获取英雄飞机的位置
	POINT GetHeroPoint();

	//碰撞检测
	void PengZhuangJianCe();

	//绘制.写在这个类中不合适
	void Paint(HWND hWnd);

	//随机添加敌机
	void AddEmenyPlane();

	void Brom();
};

#endif