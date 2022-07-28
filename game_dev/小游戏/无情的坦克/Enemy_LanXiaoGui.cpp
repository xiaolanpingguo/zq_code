#include "Enemy_LanXiaoGui.h"
#include "Bullet_LanXiaoGui.h"
CEnemy_LanXiaoGui :: CEnemy_LanXiaoGui(int hp,int att,int dir,int type,bool move,int x,int y)
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
CEnemy_LanXiaoGui :: ~CEnemy_LanXiaoGui()
{
}
int CEnemy_LanXiaoGui :: GetHp()
{
	return this->m_iHp;
}
void CEnemy_LanXiaoGui :: SetHp(int hp)
{
	this->m_iHp = hp;
}
void CEnemy_LanXiaoGui :: SetDir(char dir)
{
	this->m_iDir = dir;
}
int CEnemy_LanXiaoGui :: GetDir()
{
	return this->m_iDir;
}
int CEnemy_LanXiaoGui :: GetType()
{
	return this->m_iEnemyType;
}
void CEnemy_LanXiaoGui :: SetMove(bool move)
{
	this->m_bMove = move;
}
int CEnemy_LanXiaoGui :: GetMove()
{
	return this->m_bMove;
}
void CEnemy_LanXiaoGui :: SetEnemyPoint(POINT p)
{
	this->m_pPoint = p;
}
POINT CEnemy_LanXiaoGui :: GetEnemyPoint()
{
	return this->m_pPoint;
}
void CEnemy_LanXiaoGui :: EnemyAttack(POINT p,int dir,std::vector<CBullet*>& vBullet)
{
	CBullet *bullet = new CBullet_LanXiaoGui(p,dir,m_iAttack,rand()%4);
	vBullet.push_back(bullet);
}
void CEnemy_LanXiaoGui :: EnemyRun(int bianjieR,int bianjieD)
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
