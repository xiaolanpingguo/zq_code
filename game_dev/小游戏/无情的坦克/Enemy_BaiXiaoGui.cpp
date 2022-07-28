#include "Enemy_BaiXiaoGui.h"
#include "Bullet_BaiXiaoGui.h"
CEnemy_BaiXiaoGui :: CEnemy_BaiXiaoGui(int hp,int att,int dir,int type,bool move,int x,int y)
:
m_iHp(hp),
m_iAttack(att),
m_iDir(dir),
m_iEnemyType(type),
m_bMove(move)
{
	this->m_pPoint.x = x;
	this->m_pPoint.y = y;
}
CEnemy_BaiXiaoGui :: ~CEnemy_BaiXiaoGui()
{
}
int CEnemy_BaiXiaoGui :: GetHp()
{
	return this->m_iHp;
}
void CEnemy_BaiXiaoGui :: SetHp(int hp)
{
	this->m_iHp = hp;
}
void CEnemy_BaiXiaoGui :: SetDir(char dir)
{
	this->m_iDir = dir;
}
int CEnemy_BaiXiaoGui :: GetDir()
{
	return this->m_iDir;
}
int CEnemy_BaiXiaoGui :: GetType()
{
	return this->m_iEnemyType;
}
void CEnemy_BaiXiaoGui :: SetMove(bool move)
{
	this->m_bMove = move;
}
int CEnemy_BaiXiaoGui :: GetMove()
{
	return this->m_bMove;
}
void CEnemy_BaiXiaoGui :: SetEnemyPoint(POINT p)
{
	this->m_pPoint = p;
}
POINT CEnemy_BaiXiaoGui :: GetEnemyPoint()
{
	return this->m_pPoint;
}
void CEnemy_BaiXiaoGui :: EnemyAttack(POINT p,int dir,std::vector<CBullet*>& vBullet)
{
	CBullet *bullet = new CBullet_BaiXiaoGui(p,dir,m_iAttack,rand()%4);
	vBullet.push_back(bullet);
}
void CEnemy_BaiXiaoGui :: EnemyRun(int bianjieR,int bianjieD)
{			
	if(m_bMove)
	{
		if(this->m_iDir == 0)
		{
			if(this->m_pPoint.y>=80 )
				this->m_pPoint.y -= PIXEL_MOVE;
			else 
				this->m_iDir = rand()%4;
		}
		if(this->m_iDir == 1)
		{
			if(this->m_pPoint.y<=bianjieD -ENEMY_H) 
				this->m_pPoint.y += PIXEL_MOVE;
			else 
				this->m_iDir = rand()%4;
		}
		if(this->m_iDir == 2)
		{
			if(this->m_pPoint.x>=0 )
				this->m_pPoint.x -= PIXEL_MOVE;
			else
				this->m_iDir = rand()%4;
		}
		if(this->m_iDir == 3)
		{
			if(this->m_pPoint.x<=bianjieR-ENEMY_W)
				this->m_pPoint.x += PIXEL_MOVE;
			else 
				this->m_iDir = rand()%4;
		}	
	}
}

