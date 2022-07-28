#ifndef _ITEMS_H_
#define _ITEMS_H_
#include <vector>
#include <string>
#include <windows.h>
class CItems
{
	//道具名字
	std::string m_sName;
	//道具防御力
	int m_iDefence;
	//攻击力
	int m_iAttack;
	//血量
	int m_iHp;
	//是否出现
	bool m_bDisapper;
	//储存道具矩形
	RECT m_rRect;
public:
	CItems();
	virtual ~CItems();
	//获得道具防御力
	virtual int GetDefence();
	//获得道具攻击
	virtual int GetAtt();
	//获得道具血量
	virtual int GetHp();
	//设置是否出现
	virtual void SetApper(bool apper);
	//得到当前是否出现
	virtual bool GetApper();
	//设置矩形
	virtual void SetRect(RECT r);
	//得到道具的名字
	virtual std::string  GetName();
	//得到道具的矩形
	virtual RECT GetRect();
};
#endif