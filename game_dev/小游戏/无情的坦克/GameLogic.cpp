#include "GameLogic.h"
#include <Windows.h>
#include "GameEngine.h"
#include "Player1Bullet.h"
#include "Boom_Player_Enemy.h"
#include "Boom_Enemy_Player.h"
#include "Boom_Player_ZhangAi.h"
#include "Boom_Enemy_ZhangAi.h"
#include "Items_ShenLvMoGu.h"
#include "Items_QianLvMoGu.h"
#include "Items_HongMoGu.h"
#include "Enemy_BaiXiaoGui.h"
#include "Enemy_BaiXiaoHua.h"
#include "Enemy_HeiXiaoGui.h"
#include "Enemy_LanXiaoGui.h"
#include "Bullet_BaiXiaoGui.h"
#include "Bullet_BaiXiaoHua.h"
#include "Bullet_HeiXiaoGui.h"
#include "Bullet_LanXiaoGui.h"
using namespace std;
//敌人，玩家运动的方向
#define _DIR_UP_	0
#define _DIR_DOWN_	1
#define _DIR_LEFT_	2
#define _DIR_RIGHT_ 3
//敌人类型
#define E_BAIXIAOGUI_ 0
#define E_HEIXIAOGUI_ 1
#define E_LANXIAOGUI_ 2
#define E_BAIXIAOHUA_ 3

//格子宽高
#define GRID_W 40
#define GRID_H 40
//玩家各自宽高
#define PLAYER_W 40
#define PLAYER_H 40
//游戏显示信息区的高
#define INFO_H 80
//第一关地图障碍
static char map1[]={
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,1,0,0,1,4,0,0,0,0,3,0,3,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,
		0,0,3,0,0,0,4,0,0,0,1,4,0,0,0,0,2,0,4,0,
		0,0,0,2,0,0,0,0,1,0,0,0,1,0,0,2,0,2,0,0,
		1,0,3,0,3,0,0,1,0,0,0,4,0,1,0,1,4,0,0,1,
		1,0,0,0,0,2,1,0,0,0,4,0,0,2,0,0,1,0,0,1,
		1,1,4,1,0,0,0,0,0,1,2,0,0,0,4,0,0,0,0,0,
		0,0,0,1,0,0,0,1,0,0,0,0,1,2,0,0,1,4,0,0,
		1,0,0,0,3,0,0,2,0,1,0,0,0,1,0,0,0,0,0,1,
		1,0,0,0,1,0,4,0,0,0,0,3,0,1,0,0,0,0,1,0,
		0,0,0,0,1,1,0,0,1,0,0,1,0,0,1,0,1,0,0,0,
		0,1,1,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,1,2
	};
//构造和析构
CGameLogic :: CGameLogic()
{
	this->m_pPlayer = new CPlayer(10,0,1);
}
//析构函数，释放开的堆
CGameLogic :: ~CGameLogic()
{
	delete m_pPlayer;
	for(std::vector<CBullet*> ::iterator i = m_vPlayer1Bullet.begin(); i!=m_vPlayer1Bullet.end();++i)
		delete (*i);
	for(std::vector<CBullet*> ::iterator i = m_vEnemyBullet.begin(); i!=m_vEnemyBullet.end();++i)
		delete (*i);
	for(std::vector<CEnemy*> ::iterator i = m_vEnemy.begin(); i!=m_vEnemy.end();++i)
		delete (*i);
	for(std::vector<CBoom*> ::iterator i = m_vBoom.begin(); i!=m_vBoom.end();++i)
		delete (*i);
	for(std::vector<CItems*> ::iterator i = m_vItems.begin(); i!=m_vItems.end();++i)
		delete (*i);
}
//保存游戏
void CGameLogic ::  WriteGame()
{
	//保存游戏的分数，生命，攻击等
	CGameEngine::GetGE()->GetWF()->Create();
	CGameEngine::GetGE()->GetWF()->WriteMemory(&m_iStage,4);
	CGameEngine::GetGE()->GetWF()->WriteMemory(&m_BianJieD,4);
	CGameEngine::GetGE()->GetWF()->WriteMemory(&m_BianJieR,4);
	CGameEngine::GetGE()->GetWF()->WriteMemory(&m_iEnemyNum,4);
	CGameEngine::GetGE()->GetWF()->WriteMemory(&m_iScore,4);
	CGameEngine::GetGE()->GetWF()->WriteMemory(&m_ItemsNum,4);
	int att = m_pPlayer->GetAttack();
	int dir = m_pPlayer->GetDir();
	int life = m_pPlayer->GetLife();
	POINT p = {0,560};
	CGameEngine::GetGE()->GetWF()->WriteMemory(&att,4);
	CGameEngine::GetGE()->GetWF()->WriteMemory(&dir,4);
	CGameEngine::GetGE()->GetWF()->WriteMemory(&life,4);
	CGameEngine::GetGE()->GetWF()->WriteMemory(&p,sizeof(POINT));
	CGameEngine::GetGE()->GetWF()->Write("save\\save1");
}
//初始化地图元素表
void CGameLogic :: SetMapStage1()
{
	for(int i = 0;i < 15; ++i)
	{
		for(int j = 0;j < 20 ;++j)
		{
			if(::map1[j+i*20] >= 1)
			{
				//把当前地图的障碍储存在一个表里面
				ZHANGAI za;
				RECT r={j*40,i*40,j*40+40,i*40+40};
				za.m_iType = ::map1[j+i*20];
				if(za.m_iType == 1)
					za.m_iDefence = 6;
				switch (za.m_iType)
				{
				case 1:za.m_iDefence = 6 ;break;
				case 2:za.m_iDefence = 10 ;break;
				case 3:za.m_iDefence = -1 ;break;
				case 4:za.m_iDefence = -1 ;break;
				}
				za.m_rRect =r;
				this->m_vZhangAi.push_back(za);
			}
		}
	}
}
//游戏初始化
void CGameLogic :: GameInit()
{
	//得到当前客户区宽高
	int w = CGameEngine::GetGE()->GetW();
	int h = CGameEngine::GetGE()->GetH();
	//初始化分数，敌人最大数量，实例化玩家对象
	this->m_iStage = 1;
	this->m_iScore = 0;
	this->m_ItemsNum = 0;
	this->m_iEnemyNum = 30;
	this->m_BianJieR = w;
	this->m_BianJieD = h;
	this->m_pPlayer->SetAttack(1);
	this->m_pPlayer->SetDir(0);
	this->m_pPlayer->SetLife(30);
	POINT p={0,560};
	this->m_pPlayer->SetPlayerPoint(p);
	//清空表
	this->m_vPlayer1Bullet.clear();
	this->m_vEnemyBullet.clear();
	this->m_vEnemy.clear();
	this->m_vBoom.clear();
	this->m_vZhangAi.clear();
	this->m_vItems.clear();
	//设置道具数量
	//每个设置为3个
	for(int i =0 ;i<3;++i)
	{
		CItems* p = new CShenLvMoGU("深绿蘑菇",5,0,0,false);
		m_vItems.push_back(p);
	}
	for(int i =0 ;i<3;++i)
	{
		CItems* p = new CQianLvMoGU("浅绿蘑菇",0,5,0,false);
		m_vItems.push_back(p);
	}
	for(int i =0 ;i<3;++i)
	{
		CItems* p = new CHongMoGU("红蘑菇",0,0,5,false);
		m_vItems.push_back(p);
	}
	
}
//设置当前关卡
void CGameLogic :: SetStage(int stage)
{
	this->m_iStage = stage;
}
//设置玩家攻击
void CGameLogic :: SetPlayerAtt(int att)
{
	this->m_pPlayer->SetAttack(att);
}
//设置玩家生命
void CGameLogic :: SetPlayerLife(int life)
{
	this->m_pPlayer->SetLife(life);
}
//设置玩家类指针
CPlayer* CGameLogic :: GetPlayer()
{
	return this->m_pPlayer;
}
//设置客户区右边界
void CGameLogic :: SetBianjieR(int bianjieR)
{
	this->m_BianJieR = bianjieR;
}
//设置客户区左边界
void CGameLogic ::SetBianjieD(int bianjieD)
{
	this->m_BianJieD = bianjieD;
}
//设置分数
void CGameLogic ::SetScore(int score)
{
	this->m_iScore = score;
}
//设置道具数量
void CGameLogic ::SetItemsNum(int itemnum)
{
	this->m_ItemsNum = itemnum;
}
//设置敌人数量
void CGameLogic ::SetEnemyNum(int enemynum)
{
	this->m_iEnemyNum = enemynum;
}
//获得玩家生命值
int CGameLogic :: GetPlayerLife()
{
	return m_pPlayer->GetLife();
}
//设置玩家的攻击
void CGameLogic :: SetPlayerAttack(POINT p)
{
	this->m_pPlayer->PlayerAttack(p,m_vPlayer1Bullet);
}
//设置玩家的方向
void CGameLogic :: SetPlayerDir(char dir)
{
	this->m_pPlayer->SetDir(dir);
}
//设置玩家的位置
void CGameLogic :: SetPlayerPoint(POINT p)
{
	this->m_pPlayer->SetPlayerPoint(p);
}
//获得玩家的位置
POINT CGameLogic :: GetPlayerPoint()
{
	return this->m_pPlayer->GetPlayerPoint();
}
//获得敌人最后的数量
int CGameLogic :: GetEnemyNum()
{
	return this->m_iEnemyNum;
}
//玩家1的操作移动
void CGameLogic :: PlayerMove()
{
	//边界判断
	if( GetPlayerPoint().x>=0 && GetPlayerPoint().x <=m_BianJieR
		&& GetPlayerPoint().y>=0 && GetPlayerPoint().y<=m_BianJieD)
	{
		POINT p;
		RECT heroRect;//英雄矩形
		RECT enemyRect;//敌人矩形
		RECT linshiRect;//临时矩形
		bool pengzhuang =false;
		//上操作
		if (CGameEngine::GetGE()->GetGI()->Get(_GI_K_W) == _KS_DH)
		{	
			SetPlayerDir(_DIR_UP_);
			p.x = GetPlayerPoint().x;
			p.y = GetPlayerPoint().y - 5;
			heroRect.left = p.x;
			heroRect.top = p.y;
			heroRect.right = p.x +PLAYER_H;
			heroRect.bottom = p.y +PLAYER_H;
			//碰到障碍无法前进
			for(std::vector<ZHANGAI> ::iterator i=m_vZhangAi.begin();i!=m_vZhangAi.end();++i)
			{
				if(IntersectRect(&linshiRect,&heroRect,&i->m_rRect))
					return;
			}
			//碰到敌人无法前进
			for(std::vector<CEnemy*>::iterator i = m_vEnemy.begin(); i != m_vEnemy.end();++i)
			{
				enemyRect.left = (*i)->GetEnemyPoint().x;
				enemyRect.top = (*i)->GetEnemyPoint().y;
				enemyRect.right =(*i)->GetEnemyPoint().x +40;
				enemyRect.bottom = (*i)->GetEnemyPoint().y +40 ;
				if(IntersectRect(&linshiRect,&heroRect,&enemyRect))
						return ;
			}
			//如果都没有，即可以移动
			if(!pengzhuang)
				SetPlayerPoint(p);
			if(p.y < 80)
			{
				p.y = 80;
				SetPlayerPoint(p);
			}
			
		}
		//下操作
		if (CGameEngine::GetGE()->GetGI()->Get(_GI_K_S) == _KS_DH)
		{
			p.x = GetPlayerPoint().x;
			p.y = GetPlayerPoint().y + 5;
			SetPlayerDir(_DIR_DOWN_);
			heroRect.left = p.x;
			heroRect.top = p.y;
			heroRect.right = p.x +PLAYER_H;
			heroRect.bottom = p.y +PLAYER_H;
			//碰到障碍无法前进
			for(std::vector<ZHANGAI> ::iterator i=m_vZhangAi.begin();i!=m_vZhangAi.end();++i)
			{
				if(IntersectRect(&linshiRect,&heroRect,&i->m_rRect))
					return;
			}
			//碰到敌人无法前进
			for(std::vector<CEnemy*>::iterator i = m_vEnemy.begin(); i != m_vEnemy.end();++i)
			{
				enemyRect.left = (*i)->GetEnemyPoint().x;
				enemyRect.top = (*i)->GetEnemyPoint().y;
				enemyRect.right =(*i)->GetEnemyPoint().x +40;
				enemyRect.bottom = (*i)->GetEnemyPoint().y +40 ;
				if(IntersectRect(&linshiRect,&heroRect,&enemyRect))
						return ;
			}
			//如果都没有，即可以前进
			if(!pengzhuang)
				SetPlayerPoint(p);
			if(p.y > m_BianJieD - 40)
			{
				p.y = m_BianJieD - 40;
				SetPlayerPoint(p);
			}
			
		}
		//左操作
		if (CGameEngine::GetGE()->GetGI()->Get(_GI_K_A) == _KS_DH)
		{
			p.x = GetPlayerPoint().x -5;
			p.y = GetPlayerPoint().y;
			SetPlayerDir(_DIR_LEFT_);
					heroRect.left = p.x;
			heroRect.top = p.y;
			heroRect.right = p.x +PLAYER_W;
			heroRect.bottom = p.y +PLAYER_W;
			//碰到障碍无法前进
			for(std::vector<ZHANGAI> ::iterator i=m_vZhangAi.begin();i!=m_vZhangAi.end();++i)
			{
				if(IntersectRect(&linshiRect,&heroRect,&i->m_rRect))
					return;
			}
			//碰到敌人无法前进
			for(std::vector<CEnemy*>::iterator i = m_vEnemy.begin(); i != m_vEnemy.end();++i)
			{
				enemyRect.left = (*i)->GetEnemyPoint().x;
				enemyRect.top = (*i)->GetEnemyPoint().y;
				enemyRect.right =(*i)->GetEnemyPoint().x +40;
				enemyRect.bottom = (*i)->GetEnemyPoint().y +40 ;
				if(IntersectRect(&linshiRect,&heroRect,&enemyRect))
						return ;
			}
			//如果都没有，即可以前进
			if(!pengzhuang)
				SetPlayerPoint(p);
			if(p.x<0)
			{
				p.x=0;
				SetPlayerPoint(p);
			}
		}
		//右操作
		if (CGameEngine::GetGE()->GetGI()->Get(_GI_K_D) == _KS_DH)
		{
			p.x = GetPlayerPoint().x + 5;
			p.y = GetPlayerPoint().y ;
			SetPlayerDir(_DIR_RIGHT_);
			heroRect.left = p.x;
			heroRect.top = p.y;
			heroRect.right = p.x +PLAYER_W;
			heroRect.bottom = p.y +PLAYER_W;
			//碰到障碍无法前进
			for(std::vector<ZHANGAI> ::iterator i=m_vZhangAi.begin();i!=m_vZhangAi.end();++i)
			{
				if(IntersectRect(&linshiRect,&heroRect,&i->m_rRect))
					return;
			}
			//碰到敌人无法前进
			for(std::vector<CEnemy*>::iterator i = m_vEnemy.begin(); i != m_vEnemy.end();++i)
			{
				enemyRect.left = (*i)->GetEnemyPoint().x;
				enemyRect.top = (*i)->GetEnemyPoint().y;
				enemyRect.right =(*i)->GetEnemyPoint().x +40;
				enemyRect.bottom = (*i)->GetEnemyPoint().y +40 ;
				if(IntersectRect(&linshiRect,&heroRect,&enemyRect))
						return ;
			}
			//如果都没有，即可以前进
			if(!pengzhuang)
				SetPlayerPoint(p);
			if(p.x > m_BianJieR - 40)
			{
				p.x = m_BianJieR - 40;
				SetPlayerPoint(p);
			}
		}
	}
	//发射键
	if (CGameEngine::GetGE()->GetGI()->Get(_GI_K_J) == _KS_DC)
	{
			SetPlayerAttack(GetPlayerPoint());
			CGameEngine::GetGE()->GetAM()->PlayOnceAudio("玩家射击");
	}
}
//产生道具
void CGameLogic :: CreateItems()
{
	RECT itemRect;
	RECT linshiRect;
	//几率为20%，并且地图最多出现3个道具
	if( rand()% 20 == 0 && m_ItemsNum <3)
	{
		int x = rand() % (this->m_BianJieR - 40);
		int y = rand() % 200 + 80;
		itemRect.left = x;
		itemRect.top = y ;
		itemRect.right = x + 40;
		itemRect.bottom = y + 40;
		//出现的位置不能和障碍重合
		for(vector<ZHANGAI> ::iterator j=m_vZhangAi.begin();j!=m_vZhangAi.end();++j)
		{
			if(IntersectRect(&linshiRect,&itemRect,&j->m_rRect))
				return ;
		}
		int suiji = rand()% 9;
		for(int i=0;i< (int)m_vItems.size(); ++i)
		{
			if(suiji == i && !m_vItems.at(i)->GetApper())
			{
				//出现红蘑菇
				if(strcmp(m_vItems.at(i)->GetName().c_str(),"红蘑菇") == 0)
				{
					m_vItems.at(i)->SetRect(itemRect);
					m_vItems.at(i)->SetApper(true);
				}
				//出现深绿蘑菇
				if(strcmp(m_vItems.at(i)->GetName().c_str(),"深绿蘑菇") == 0)
				{
					m_vItems.at(i)->SetRect(itemRect);
					m_vItems.at(i)->SetApper(true);
				}
				//出现浅绿蘑菇
				if(strcmp(m_vItems.at(i)->GetName().c_str(),"浅绿蘑菇") == 0)
				{
					m_vItems.at(i)->SetRect(itemRect);
					m_vItems.at(i)->SetApper(true);
				}
				m_ItemsNum ++ ;
				break;
			}
		}
	}
}
//捡到道具
void CGameLogic :: PlayerGetItem()
{
	RECT heroRect;//英雄矩形
	RECT linshiRect;//临时矩形
	//获得英雄位置
	heroRect.left = m_pPlayer->GetPlayerPoint().x;
	heroRect.top = m_pPlayer->GetPlayerPoint().y;
	heroRect.right = m_pPlayer->GetPlayerPoint().x + 40;
	heroRect.bottom = m_pPlayer->GetPlayerPoint().y + 40;
	//遍历道具表
	for(vector<CItems*> ::iterator i=m_vItems.begin();i!=m_vItems.end();++i)
	{
		//道具出现了才能判断
		if((*i)->GetApper())
		{
			//拾取到了道具
			if(IntersectRect(&linshiRect,&heroRect,&(*i)->GetRect()))
			{
				//根据道具类型，玩家获得相应属性
				if(strcmp((*i)->GetName().c_str(),"红蘑菇") == 0)
					m_pPlayer->SetLife(m_pPlayer->GetLife() + (*i)->GetHp());
				if(strcmp((*i)->GetName().c_str(),"深绿蘑菇") == 0)
					m_pPlayer->SetLife(m_pPlayer->GetLife() + (*i)->GetDefence());
				if(strcmp((*i)->GetName().c_str(),"浅绿蘑菇") == 0)
					m_pPlayer->SetAttack(m_pPlayer->GetAttack()+(*i)->GetAtt());
				i = m_vItems.erase(i);
				m_ItemsNum -- ;
				break;
			}
		}
	}
}
//产生敌人
void CGameLogic :: CreateEnemy()
{
	RECT heroRect;//英雄矩形
	RECT linshiRect;//临时矩形
	RECT enemyRect;//敌人矩形
	RECT enemyRect1;//敌人矩形
	//产生的敌人在客户区内
	bool add = true;
	int x = CGameEngine::GetGE()->GetW();
	x = rand() % 152;
	x *= 5;
	int y = rand() % 96;
	y *= 5;
	y += 80;
	enemyRect1.left  = x;
	enemyRect1.top = y;
	enemyRect1.right = x + 40;
	enemyRect1.bottom = y +40;
	heroRect.left = m_pPlayer->GetPlayerPoint().x;
	heroRect.top = m_pPlayer->GetPlayerPoint().y;
	heroRect.right = m_pPlayer->GetPlayerPoint().x + 40;
	heroRect.bottom = m_pPlayer->GetPlayerPoint().y + 40;
	//产生的敌人不能和玩家重合
	if(IntersectRect(&linshiRect,&enemyRect1,&heroRect))
		return;
	//产生的敌人不能和已有敌人重合
	for(std::vector<CEnemy*>::iterator i = m_vEnemy.begin(); i != m_vEnemy.end();++i)
	{
		enemyRect.left = (*i)->GetEnemyPoint().x;
		enemyRect.top = (*i)->GetEnemyPoint().y;
		enemyRect.right =(*i)->GetEnemyPoint().x +40;
		enemyRect.bottom = (*i)->GetEnemyPoint().y +40 ;
		if(IntersectRect(&linshiRect,&enemyRect1,&enemyRect))
				return ;
	}
	//产生的敌人不能和障碍重合
	for(vector<ZHANGAI> ::iterator j=m_vZhangAi.begin();j!=m_vZhangAi.end();++j)
	{
		if(IntersectRect(&linshiRect,&enemyRect1,&j->m_rRect))
			return ;
	}
	//产生敌人，最多10个
	if(rand() % 10 == 0 && add && (int)m_vEnemy.size() < m_iEnemyNum)
	{
		if(this->m_iEnemyNum > 0)
		{
			CEnemy * enemy;
			int suiji = rand()%4;
			//随机产生一种敌人
			if(suiji == E_BAIXIAOGUI_)
				enemy = new CEnemy_BaiXiaoGui(2,2,rand()%4,E_BAIXIAOGUI_,true,enemyRect1.left,enemyRect1.top);
			if(suiji == E_HEIXIAOGUI_)
				enemy = new CEnemy_HeiXiaoGui(2,6,rand()%4,E_HEIXIAOGUI_,true,enemyRect1.left,enemyRect1.top);
			if(suiji == E_LANXIAOGUI_)
				enemy = new CEnemy_LanXiaoGui(3,5,rand()%4,E_LANXIAOGUI_,true,enemyRect1.left,enemyRect1.top);
			if(suiji == E_BAIXIAOHUA_)
				enemy = new CEnemy_BaiXiaoHua(4,8,rand()%4,E_BAIXIAOHUA_,true,enemyRect1.left,enemyRect1.top);
			this->m_vEnemy.push_back(enemy);
		}
	}
}
//----游戏运行----
//-------包括-----
//---敌人的运行--
//---子弹的运行--
//---碰撞的检测--
void CGameLogic :: GameRun()
{
	RECT enemyBulletRect;//敌人子弹矩形
	RECT heroBulletRect;//英雄子弹矩形
	RECT linshiRect;//临时矩形
	//产生敌人
	CreateEnemy();
	//产生道具
	CreateItems();
	//拾取道具检测
	PlayerGetItem();
	//碰撞检测
	PengZhaungJianCe();
	//敌人的运行，发子弹
	for(vector<CEnemy*>::iterator i=m_vEnemy.begin();i!=m_vEnemy.end();++i)
	{
		//20%几率发一颗子弹
		if(rand() % 10 == 0)
		{
			if((*i)->GetType() == E_BAIXIAOGUI_)
				(*i)->EnemyAttack((*i)->GetEnemyPoint(),(*i)->GetDir(),this->m_vEnemyBullet);
			if((*i)->GetType() == E_BAIXIAOHUA_)
				(*i)->EnemyAttack((*i)->GetEnemyPoint(),(*i)->GetDir(),this->m_vEnemyBullet);
			if((*i)->GetType() == E_HEIXIAOGUI_)
				(*i)->EnemyAttack((*i)->GetEnemyPoint(),(*i)->GetDir(),this->m_vEnemyBullet);
			if((*i)->GetType() == E_LANXIAOGUI_)
				(*i)->EnemyAttack((*i)->GetEnemyPoint(),(*i)->GetDir(),this->m_vEnemyBullet);
			CGameEngine::GetGE()->GetAM()->PlayOnceAudio("敌人射击");
		}
		(*i)->EnemyRun(this->m_BianJieR,this->m_BianJieD);
	}
	//玩家1的子弹与障碍的碰撞
	for(vector<CBullet*>::iterator i=m_vPlayer1Bullet.begin();i!=m_vPlayer1Bullet.end();)
	{
		bool ereas = false;
		heroBulletRect.left = (*i)->GetBulletPoint().x ;
		heroBulletRect.top = (*i)->GetBulletPoint().y ;
		heroBulletRect.right = (*i)->GetBulletPoint().x + 20;
		heroBulletRect.bottom = (*i)->GetBulletPoint().y + 20;
		for(vector<ZHANGAI> ::iterator j=m_vZhangAi.begin();j!=m_vZhangAi.end();++j)
		{
			if(IntersectRect(&linshiRect,&heroBulletRect,&j->m_rRect))
			{
				//检测到了，把爆炸效果推入爆炸表
				CBoom *pBoom= new CBoom_Player_ZhangAi(linshiRect,0);
				this->m_vBoom.push_back(pBoom);
				//根据障碍的防御力，来判断障碍是否被摧毁
				if(j->m_iType ==1 || j->m_iType == 2)
				{
					j->m_iDefence -= 2;
					if(	j->m_iDefence <= 0)
						j = m_vZhangAi.erase(j);
				}
				//删除子弹
				CBullet * pBullet = (*i);
				i = m_vPlayer1Bullet.erase(i);
				delete pBullet;
				ereas =true;
				break;
			}
		}
		if(!ereas)
			++i;
	}
	//玩家1子弹运行
	for(vector<CBullet*>::iterator i=m_vPlayer1Bullet.begin();i!=m_vPlayer1Bullet.end();)
	{
		//超过边界销毁
		if(!(*i)->BulletRun(m_BianJieR,m_BianJieD))
		{
			CBullet *pBullet = (*i);
			i=m_vPlayer1Bullet.erase(i);
			delete pBullet;
		}
		else
			++i;
	}
	//敌人子弹与障碍之间的碰撞
	for(vector<CBullet*>::iterator i=m_vEnemyBullet.begin();i!=m_vEnemyBullet.end();)
	{
		bool ereas = false;
		enemyBulletRect.left = (*i)->GetBulletPoint().x;
		enemyBulletRect.top = (*i)->GetBulletPoint().y;
		enemyBulletRect.right = (*i)->GetBulletPoint().x + 16;
		enemyBulletRect.bottom = (*i)->GetBulletPoint().y + 16;
		for(vector<ZHANGAI> ::iterator j=m_vZhangAi.begin();j!=m_vZhangAi.end();++j)
		{
			if(IntersectRect(&linshiRect,&enemyBulletRect,&j->m_rRect))
			{
				//根据障碍的防御力，来判断障碍是否被摧毁
				CBoom *pBoom= new CBoom_Enemy_ZhangAi(linshiRect,0);
				this->m_vBoom.push_back(pBoom);
				if(j->m_iType ==1 || j->m_iType == 2)
				{
					j->m_iDefence -= 1;
					if(	j->m_iDefence <= 0)
						j = m_vZhangAi.erase(j);
				}
				//删除子弹
				CBullet * pBullet = (*i);
				i = m_vEnemyBullet.erase(i);
				delete pBullet;
				ereas =true;
				break;
			}
		}
		if(!ereas)
			++i;
	}
	//敌人的子弹，运行
	for(vector<CBullet*>::iterator i=m_vEnemyBullet.begin();i!=m_vEnemyBullet.end();)
	{
		//子弹超出边界销毁
		if(!(*i)->BulletRun(m_BianJieR,m_BianJieD))
		{
			CBullet *pBullet = (*i);
			i=m_vEnemyBullet.erase(i);
			delete pBullet;
		}
		else
			++i;
	}
}
//碰撞检测
void CGameLogic :: PengZhaungJianCe()
{
	RECT heroRect;//英雄矩形
	RECT linshiRect;//临时矩形
	RECT enemyRect;//敌人矩形
	RECT enemyRect1;
	RECT enemyBulletRect;//敌人子弹矩形
	RECT heroBulletRect;//英雄子弹矩形
	//敌人子弹与1号玩家的碰撞
	for(std::vector<CBullet*>::iterator i = m_vEnemyBullet.begin(); i!= m_vEnemyBullet.end();)
	{
		heroRect.left = m_pPlayer->GetPlayerPoint().x;
		heroRect.top = m_pPlayer->GetPlayerPoint().y;
		heroRect.right = m_pPlayer->GetPlayerPoint().x + 40;
		heroRect.bottom = m_pPlayer->GetPlayerPoint().y + 40;
		
		enemyBulletRect.left = (*i)->GetBulletPoint().x;
		enemyBulletRect.top = (*i)->GetBulletPoint().y;
		enemyBulletRect.right = (*i)->GetBulletPoint().x + 16;
		enemyBulletRect.bottom = (*i)->GetBulletPoint().y + 16;
		//检测成功
		if(IntersectRect(&linshiRect,&heroRect,&enemyBulletRect))
		{
			//把爆炸矩形推入爆炸表
			CGameEngine::GetGE()->GetAM()->PlayOnceAudio("爆炸");
			m_pPlayer->SetLife(m_pPlayer->GetLife() -(*i)->GetAttack());
			CBoom *pBoom= new CBoom_Enemy_Player(linshiRect,0);
			this->m_vBoom.push_back(pBoom);
			//删除子弹
			CBullet* bullet = (*i);
			i = m_vEnemyBullet.erase(i);
			delete bullet;
		}
		else
			++i;
	}
	//敌人与敌人,玩家，障碍之间相互的碰撞，碰撞后改变方向
	for(std::vector<CEnemy*>::iterator i = m_vEnemy.begin(); i != m_vEnemy.end();++i)
	{
		//判断当前位置的下个位置，并设置敌人可以移动
		(*i)->SetMove(true);
		//判断的四个方向，上下左右
		RECT r[4];

			r[0].left = (*i)->GetEnemyPoint().x;
			r[0].top = (*i)->GetEnemyPoint().y-5;
			r[0].right =(*i)->GetEnemyPoint().x + 40;
			r[0].bottom = (*i)->GetEnemyPoint().y + 40-5;

			r[1].left = (*i)->GetEnemyPoint().x;
			r[1].top = (*i)->GetEnemyPoint().y+5;
			r[1].right =(*i)->GetEnemyPoint().x + 40;
			r[1].bottom = (*i)->GetEnemyPoint().y + 40+5;

			r[2].left = (*i)->GetEnemyPoint().x-5;
			r[2].top = (*i)->GetEnemyPoint().y;
			r[2].right =(*i)->GetEnemyPoint().x + 40-5;
			r[2].bottom = (*i)->GetEnemyPoint().y + 40;

			r[3].left = (*i)->GetEnemyPoint().x+5;
			r[3].top = (*i)->GetEnemyPoint().y;
			r[3].right =(*i)->GetEnemyPoint().x + 40+5;
			r[3].bottom = (*i)->GetEnemyPoint().y + 40;
		//定义临时的4个标志，用来记录当前方向是否可以移动
		bool flag[4] = {};
		//4个方向
		for(int k = 0;k < 4; ++k)
		{
			//当前方向是否有敌人
			for(std::vector<CEnemy*>::iterator j = m_vEnemy.begin(); j != m_vEnemy.end(); ++j)
			{
				//获取要检测碰撞的敌人的位置
				enemyRect1.left = (*j)->GetEnemyPoint().x ;
				enemyRect1.top = (*j)->GetEnemyPoint().y ;
				enemyRect1.right = (*j)->GetEnemyPoint().x + 40;
				enemyRect1.bottom = (*j)->GetEnemyPoint().y + 40;
				if( (*i) != (*j))
				{
					//检测成功，当前方向不能移动，设置标志为TRUE
					if(IntersectRect(&linshiRect,&r[k],&enemyRect1))
					{						
						flag[k] = true;
						break;
					}
				}//是否相等括号
			}
			//---------与玩家碰撞的检测-------
			//获取当前玩家的位置
			heroRect.left = m_pPlayer->GetPlayerPoint().x;
			heroRect.top = m_pPlayer->GetPlayerPoint().y;
			heroRect.right = m_pPlayer->GetPlayerPoint().x + 40;
			heroRect.bottom = m_pPlayer->GetPlayerPoint().y + 40;
			//检测成功，当前方向标志为TRUE
			if(IntersectRect(&linshiRect,&heroRect,&r[k]))
				flag[k] = true ;
			//--------与障碍之间的碰撞------------
			for(std::vector<ZHANGAI> ::iterator j=m_vZhangAi.begin();j!=m_vZhangAi.end();++j)
			{
				//检测成功，当前方向标志为TRUE
				if(IntersectRect(&linshiRect,&r[k],&j->m_rRect))
				{						
					flag[k] = true;
					break;
				}
			}
		}
		//当这个方向不能移动时，即要改变方向
		if(flag[(*i)->GetDir()] )
		{
			int suiji=0;
			//改变方向，直到随机产出的方向能移动
			do
			{
				//如果4个方向都不能移动，设置不能移动
				if(flag[0] &&flag[1]&&flag[2]&&flag[3])
				{
					(*i)->SetMove(false);
					break;
				}
				else
					suiji =rand()%4;
			}while(flag[suiji]);
			(*i)->SetDir(suiji);
		}
	}//外层for括号
	//玩家子弹与敌人的碰撞
	for(std::vector<CBullet*>::iterator i = m_vPlayer1Bullet.begin(); i != m_vPlayer1Bullet.end();)
	{
		bool erase = false;
		
		for(std::vector<CEnemy*>::iterator j = m_vEnemy.begin(); j!= m_vEnemy.end();++j)
		{
			enemyRect.left = (*j)->GetEnemyPoint().x;
			enemyRect.top = (*j)->GetEnemyPoint().y;
			enemyRect.right = (*j)->GetEnemyPoint().x + 40;
			enemyRect.bottom = (*j)->GetEnemyPoint().y + 40;
			
			heroBulletRect.left = (*i)->GetBulletPoint().x ;
			heroBulletRect.top = (*i)->GetBulletPoint().y ;
			heroBulletRect.right = (*i)->GetBulletPoint().x + 20;
			heroBulletRect.bottom = (*i)->GetBulletPoint().y + 20;
			//检测成功，删除子弹
			if(IntersectRect(&linshiRect,&heroBulletRect,&enemyRect))
			{
				if((*j)->GetHp()<=0)
				{
					CEnemy* enemy = (*j);
					m_vEnemy.erase(j);
					delete enemy;
					m_iScore++;
					this->m_iEnemyNum -- ;
				}
				//根据敌人类型来设置敌人的相应属性
				else
					(*j)->SetHp((*j)->GetHp()-(*i)->GetAttack());
				//产生爆炸
				CGameEngine::GetGE()->GetAM()->PlayOnceAudio("爆炸");
				CBoom *pBoom= new CBoom_Player_Enemy(linshiRect,0);
				this->m_vBoom.push_back(pBoom);
				//删除子弹
				CBullet* pBullet = (*i); 
				i = m_vPlayer1Bullet.erase(i);
				delete pBullet;
				erase = true;
				
				break;
			}	
		}
		if(!erase)
			++i;
	}
}
//绘制函数
void CGameLogic :: Paint()
{
	//加载字体
	CGameEngine::GetGE()->GetGO()->LoadFont("游戏显示信息字体",
		15, 15, 20, false, false, false, "宋体");
	//绘制客户区上部分的背景
	CGameEngine::GetGE()->GetGO()->DrawBmp3("pic\\black.bmp",
		0, 0,this->m_BianJieR, INFO_H,0, 0,50,50);
	//绘制游戏信息（分数，生命，怪物数量等）
	char buf[16];
	sprintf_s(buf,16,"分数：%d",this->m_iScore);
	CGameEngine::GetGE()->GetGO()->DrawString1("游戏显示信息字体",0,0,buf,RGB(255,0,0));
	char buf1[16];
	sprintf_s(buf1,16,"生命：%d",this->m_pPlayer->GetLife());
	CGameEngine::GetGE()->GetGO()->DrawString1("游戏显示信息字体",150,0,buf1,RGB(255,0,0));
	char buf2[20];
	sprintf_s(buf2,20,"当前剩余敌人：%d",this->m_iEnemyNum);
	CGameEngine::GetGE()->GetGO()->DrawString1("游戏显示信息字体",0,30,buf2,RGB(255,0,0));
	char buf3[20];
	sprintf_s(buf3,20,"当前攻击力：%d",this->m_pPlayer->GetAttack());
	CGameEngine::GetGE()->GetGO()->DrawString1("游戏显示信息字体",280,0,buf3,RGB(255,0,0));
	//绘制游戏背景图
	CGameEngine::GetGE()->GetGO()->DrawBmp3("pic\\background.bmp",
		0, INFO_H, this->m_BianJieR, this->m_BianJieD,0, 0,33,30);
	//绘制地图障碍
	for(std::vector<ZHANGAI>::iterator i =m_vZhangAi.begin();i!=m_vZhangAi.end();++i)
	{
		if(i->m_iType == 1)
			CGameEngine::GetGE()->GetGO()->DrawBmp3("pic\\zhangai1.bmp",
				i->m_rRect.left, i->m_rRect.top, 40, 40,0, 0,16,15);
		if(i->m_iType == 2)
			CGameEngine::GetGE()->GetGO()->DrawBmp3("pic\\zhangai7.bmp",
				i->m_rRect.left, i->m_rRect.top, 40, 40,0, 0,16,16);
		if(i->m_iType == 3)
			CGameEngine::GetGE()->GetGO()->DrawBmp3("pic\\zhangai5.bmp",
				i->m_rRect.left, i->m_rRect.top, 40, 40,0, 0,16,16);
		if(i->m_iType == 4)
			CGameEngine::GetGE()->GetGO()->DrawBmp3("pic\\zhangai2.bmp",
				i->m_rRect.left, i->m_rRect.top, 40, 40,0, 0,16,16);
	}
	//绘制玩家1
	if(this->m_pPlayer->GetDir() == _DIR_UP_)
		CGameEngine::GetGE()->GetGO()->DrawBmp3("pic\\红龙1.bmp",
			this->GetPlayerPoint().x, this->GetPlayerPoint().y, 40, 40,0, 0,132,126,RGB(255,255,255));
	if(this->m_pPlayer->GetDir() == _DIR_DOWN_)
		CGameEngine::GetGE()->GetGO()->DrawBmp3("pic\\红龙2.bmp",
			this->GetPlayerPoint().x, this->GetPlayerPoint().y, 40, 40,0, 0,132,126,RGB(255,255,255));
	if(this->m_pPlayer->GetDir() == _DIR_LEFT_)
		CGameEngine::GetGE()->GetGO()->DrawBmp3("pic\\红龙3.bmp",
			this->GetPlayerPoint().x, this->GetPlayerPoint().y, 40, 40,0, 0,142,106,RGB(255,255,255));
	if(this->m_pPlayer->GetDir() == _DIR_RIGHT_)
		CGameEngine::GetGE()->GetGO()->DrawBmp3("pic\\红龙4.bmp",
			this->GetPlayerPoint().x, this->GetPlayerPoint().y, 40, 40,0, 0,142,106,RGB(255,255,255));
	//绘制玩家1的子弹
	for(vector<CBullet*>::iterator i=m_vPlayer1Bullet.begin();i!=m_vPlayer1Bullet.end();++i)
		CGameEngine::GetGE()->GetGO()->DrawBmp3("pic\\fireball.bmp",
			(*i)->GetBulletPoint().x,(*i)->GetBulletPoint().y, 30, 30,78, 0,13,17);
	//绘制敌人的子弹
	for(vector<CBullet*>::iterator i=m_vEnemyBullet.begin();i!=m_vEnemyBullet.end();++i)
		CGameEngine::GetGE()->GetGO()->DrawBmp3("pic\\fireball.bmp",
			(*i)->GetBulletPoint().x,(*i)->GetBulletPoint().y, 16, 16,78, 0,13,16);
	//根据敌人的类型来绘制敌人
	for(vector<CEnemy*>::iterator i=m_vEnemy.begin();i!=m_vEnemy.end();++i)
	{
		if((*i)->GetType() == 0)
			CGameEngine::GetGE()->GetGO()->DrawBmp3("pic\\Enemy1.bmp",
				(*i)->GetEnemyPoint().x,(*i)->GetEnemyPoint().y, 40, 40,60, 0,20,16);
		if((*i)->GetType() == 1)
			CGameEngine::GetGE()->GetGO()->DrawBmp3("pic\\Enemy2.bmp",
				(*i)->GetEnemyPoint().x,(*i)->GetEnemyPoint().y, 40, 40,0, 0,19,17);
		if((*i)->GetType() == 2)
			CGameEngine::GetGE()->GetGO()->DrawBmp3("pic\\Enemy3.bmp",
				(*i)->GetEnemyPoint().x,(*i)->GetEnemyPoint().y, 40, 40,0, 0,17,16);
		if((*i)->GetType() == 3)
			CGameEngine::GetGE()->GetGO()->DrawBmp3("pic\\Enemy6.bmp",
				(*i)->GetEnemyPoint().x,(*i)->GetEnemyPoint().y, 40, 40,0, 0,32,32,RGB(0,0,0));
	}
	//绘制爆炸效果
	for(vector<CBoom*>::iterator i=m_vBoom.begin();i!=m_vBoom.end();)
	{
		if(!(*i)->Run())
			i=m_vBoom.erase(i);
		else
		{
			(*i)->Paint();
			++i;
		}
	}
	//绘制道具
	for(vector<CItems*> ::iterator i=m_vItems.begin();i!=m_vItems.end();++i)
	{
		if((*i)->GetApper())
		{
			if(strcmp((*i)->GetName().c_str(),"红蘑菇") == 0)
				CGameEngine::GetGE()->GetGO()->DrawBmp3("pic\\红蘑菇.bmp",
				(*i)->GetRect().left,(*i)->GetRect().top, 40, 40,0, 0,18,17);
			if(strcmp((*i)->GetName().c_str(),"浅绿蘑菇") == 0)
				CGameEngine::GetGE()->GetGO()->DrawBmp3("pic\\浅绿蘑菇.bmp",
				(*i)->GetRect().left,(*i)->GetRect().top, 40, 40,0, 0,16,17);
			if(strcmp((*i)->GetName().c_str(),"深绿蘑菇") == 0)
				CGameEngine::GetGE()->GetGO()->DrawBmp3("pic\\深绿蘑菇.bmp",
				(*i)->GetRect().left,(*i)->GetRect().top, 40, 40,0, 0,16,16);
		}
		
	}
}	