//------------------------
//CGameRole:游戏元素(角色)类
//主要包含游戏中的人，木，箱子，困，囚，障碍
//这些游戏元素的共性:坐标，类型
//用法：通过游戏逻辑类调用相关函数
//作者：陈会均 日期：2015年3月13日
//------------------------

#ifndef _GAMEROLE_H_
#define _GAMEROLE_H_

#include "GameTool.h"

//游戏元素(角色)类
class CGameRole
{
	int m_iX;//角色的X坐标
	int m_iY;//角色的Y坐标
	Role m_role;//角色的类型，枚举
public:
	//游戏角色初始化函数,x,y,r代表x坐标，y坐标，r角色类型
	void Init(int x,//x坐标
			  int y,//y坐标
			  Role r);//角色类型
	//坐标设置函数
	void SetZuoBiao(int x,int y);

	//设置角色类型
	void SetEnumRole(Role r);

	//获取角色的X坐标
	int GetZBX();

	//获取角色的Y坐标
	int GetZBY();

	//获取角色类型
	Role GetRole();
};

#endif