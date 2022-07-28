#include "Enemy.h"

CEnemy :: CEnemy()
{
}
CEnemy :: ~CEnemy()
{
}
//获得血量
int CEnemy :: GetHp()
{
	return this->m_iHp;
}
//设置血量
void CEnemy :: SetHp(int hp)
{
	this->m_iHp = hp;
}
//设置方向
void CEnemy :: SetDir(char dir)
{
	this->m_iDir = dir;
}
//获得敌人的方向
int CEnemy :: GetDir()
{
	return this->m_iDir;
}
//获得敌人的类型
int CEnemy :: GetType()
{
	return this->m_iEnemyType;
}
//设置是否移动
void CEnemy :: SetMove(bool move)
{
	this->m_bMove = move;
}
//获得当前是否移动的标记
int CEnemy :: GetMove()
{
	return this->m_bMove;
}
//设置敌人位置
void CEnemy :: SetEnemyPoint(POINT p)
{
	this->m_pPoint = p;
}
//获得敌人的位置
POINT CEnemy :: GetEnemyPoint()
{
	return this->m_pPoint;
}
void CEnemy :: EnemyAttack(POINT p,int dir,std::vector<CBullet*>& vBullet)
{
	
}
//敌人移动，超过边界改变方向
void CEnemy :: EnemyRun(int bianjieR,int bianjieD)
{			
	if(m_bMove)
	{
		//上
		if(this->m_iDir == 0)
		{
			if(this->m_pPoint.y>=80 )
				this->m_pPoint.y -= PIXEL_MOVE;
			else 
				this->m_iDir = rand()%4;
		}
		//下
		if(this->m_iDir == 1)
		{
			if(this->m_pPoint.y<=bianjieD -ENEMY_H) 
				this->m_pPoint.y += PIXEL_MOVE;
			else 
				this->m_iDir = rand()%4;
		}
		//左
		if(this->m_iDir == 2)
		{
			if(this->m_pPoint.x>=0 )
				this->m_pPoint.x -= PIXEL_MOVE;
			else
				this->m_iDir = rand()%4;
		}
		//右
		if(this->m_iDir == 3)
		{
			if(this->m_pPoint.x<=bianjieR-ENEMY_W)
				this->m_pPoint.x += PIXEL_MOVE;
			else 
				this->m_iDir = rand()%4;
		}	
	}
}