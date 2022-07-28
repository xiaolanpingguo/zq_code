#include "Enemy_BaiXiaoHua.h"
#include "Bullet_BaiXiaoHua.h"
CEnemy_BaiXiaoHua :: CEnemy_BaiXiaoHua(int hp,int att,int dir,int type,bool move,int x,int y)
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
CEnemy_BaiXiaoHua :: ~CEnemy_BaiXiaoHua()
{
}
int CEnemy_BaiXiaoHua :: GetHp()
{
	return this->m_iHp;
}
void CEnemy_BaiXiaoHua :: SetHp(int hp)
{
	this->m_iHp = hp;
}
void CEnemy_BaiXiaoHua :: SetDir(char dir)
{
	this->m_iDir = dir;
}
int CEnemy_BaiXiaoHua :: GetDir()
{
	return this->m_iDir;
}
int CEnemy_BaiXiaoHua :: GetType()
{
	return this->m_iEnemyType;
}
void CEnemy_BaiXiaoHua :: SetMove(bool move)
{
	this->m_bMove = move;
}
int CEnemy_BaiXiaoHua :: GetMove()
{
	return this->m_bMove;
}
void CEnemy_BaiXiaoHua :: SetEnemyPoint(POINT p)
{
	this->m_pPoint = p;
}
POINT CEnemy_BaiXiaoHua :: GetEnemyPoint()
{
	return this->m_pPoint;
}
void CEnemy_BaiXiaoHua :: EnemyAttack(POINT p,int dir,std::vector<CBullet*>& vBullet)
{
	CBullet *bullet = new CBullet_BaiXiaoHua(p,dir,m_iAttack,rand()%4);
	vBullet.push_back(bullet);
}
void CEnemy_BaiXiaoHua :: EnemyRun(int bianjieR,int bianjieD)
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
