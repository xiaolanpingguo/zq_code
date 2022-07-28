#include "Player.h"
//构造函数，生命，方向，攻击
CPlayer :: CPlayer(int life,int dir,int att)
	:
	m_iLife(life),
	m_iDir(dir),
	m_iAttack(att)
{
	//初始化玩家进游戏的位置
	int x = CGameEngine::GetGE()->GetW();
	int y = CGameEngine::GetGE()->GetH();
	this->m_pPlayerPoint.x = 0;
	this->m_pPlayerPoint.y = 560;
}
CPlayer :: ~CPlayer()
{
}
//设置生命
void CPlayer :: SetLife(int life)
{
	this->m_iLife = life;
}
//获得生命
int CPlayer :: GetLife()
{
	return this->m_iLife;
}//设置方向
void CPlayer :: SetDir(int dir)
{
	this->m_iDir = dir;
}
//获得方向
int CPlayer :: GetDir()
{
	return this->m_iDir;
}
//设置攻击
void CPlayer :: SetAttack(int attack)
{
	this->m_iAttack = attack;
}
//获得攻击
int CPlayer :: GetAttack()
{
	return this->m_iAttack;
}
//获得玩家位置
POINT CPlayer :: GetPlayerPoint()
{
	return this->m_pPlayerPoint;
}
//设置玩家位置
void CPlayer :: SetPlayerPoint(POINT p)
{
	this->m_pPlayerPoint = p;
}
//玩家攻击发子弹
void CPlayer :: PlayerAttack(POINT p,std::vector<CBullet*>& vBullet)
{
	CBullet *bullet = new CPlayer1Bullet(p,m_iDir,m_iAttack,0);
	vBullet.push_back(bullet);
}
