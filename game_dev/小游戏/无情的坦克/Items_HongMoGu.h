#ifndef _ITEMS_HONGMOGU_H_
#define _ITEMS_HONGMOGU_H_
#include "Items.h"
class CHongMoGU : public CItems
{
	//道具名字
	std::string m_sName;
	//道具所属防御
	int m_iDefence;
	//道具所属攻击
	int m_iAttack;
	//道具所属血量
	int m_iHp;
	//道具是否出现
	bool m_bDisapper;
	//道具图片矩形
	RECT m_rRect;
public:
	CHongMoGU(std::string s,int de,int att,int hp,bool apper);
	~CHongMoGU();
	//获得道具的防御力
	int GetDefence();
	//获得道具的攻击力
	int GetAtt();
	//获得道具的血量
	int GetHp();
	//设置道具是否出现
	void SetApper(bool apper);
	//获得道具当前是否出现的布尔值
	bool GetApper();
	//设置道具图片的矩形
	void SetRect(RECT r);
	//获得道具图片的矩形
	RECT GetRect();
	//获得道具的名字
	std::string  GetName();
};
#endif