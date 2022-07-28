#ifndef _GAMELOGIC_H_
#define _GAMELOGIC_H_
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Boom.h"
#include "Items.h"
#include <vector>
#include <map>
#include <string>
//游戏逻辑类（总类）
class CGameLogic
{
	//地图障碍结构体
	struct ZHANGAI
	{
		int m_iType;
		int m_iDefence;
		RECT m_rRect;
	};
	//玩家类指针
	CPlayer * m_pPlayer;
	//客户区右边界和下边界
	int m_BianJieR;
	int m_BianJieD;
	//当前关卡
	int m_iStage;
	//分数
	int m_iScore;
	//已经出现的道具数量
	int m_ItemsNum;
	//当前场景剩余敌人数量
	int m_iEnemyNum;
	//玩家1的子弹
	std::vector<CBullet*> m_vPlayer1Bullet;
	//敌人子弹表
	std::vector<CBullet*> m_vEnemyBullet;
	//敌人表
	std::vector<CEnemy*> m_vEnemy;
	//地图障碍的表
	std::vector<ZHANGAI> m_vZhangAi;
	//爆炸效果表
	std::vector<CBoom*> m_vBoom;
	//道具表
	std::vector<CItems*> m_vItems;
public:
	CGameLogic();
	~CGameLogic();
	void pengzhuang();
	//游戏初始化
	void GameInit();
	//获得怪物最后的数量
	int GetEnemyNum();
	//设置客户区右边界
	void SetBianjieR(int bianjieR);
	////设置客户区下边界
	void SetBianjieD(int bianjieD);
	//设置分数
	void SetScore(int score);
	//设置关卡
	void SetStage(int stage);
	//设置道具数量
	void SetItemsNum(int itemnum);
	//设置敌人的数量
	void SetEnemyNum(int enemynum);
	//设置玩家攻击
	void SetPlayerAtt(int att);
	//设置玩家生命
	void SetPlayerLife(int life);
	//获得玩家类指针
	CPlayer* GetPlayer();
	//地图设置障碍
	void SetMapStage1();
	//游戏运行
	void GameRun();
	//绘制地图元素
	void Paint();
	//设置玩家1的方向
	void SetPlayerDir(char dir);
	//获得玩家的生命值
	int GetPlayerLife();
	//玩家1的攻击
	void SetPlayerAttack(POINT p);
	//设置玩家的位置
	void SetPlayerPoint(POINT p);
	//获得玩家的位置
	POINT GetPlayerPoint();
	//玩家的移动与操作
	void PlayerMove();
	//碰撞检测
	void PengZhaungJianCe();
	void CreateItems();
	//产生敌人
	void CreateEnemy();
	//拾取道具
	void PlayerGetItem();
	//保存游戏
	void WriteGame();
};
#endif