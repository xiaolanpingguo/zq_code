//所谓脚本（script），指的是临时加载、编译、执行的程序，一般来说
//脚本有专门的脚本语言，比如JavaScript、Lua、Python等脚本，使用
//这些脚本的方法，就是将这个脚本语言的代码写在文件中，然后在主程
//序（往往是C、C++、Java等主流语言些的程序）中加载并编译它们，然
//后执行它们，这就是脚本的工作流程，作为计算机语言来说，主要干两
//件事情，数据的定义和数据的处理，脚本语言也不例外，也可以定义和
//处理数据，定义数据比较简单，处理数据非常复杂要用到编译原理的知
//识，下面给大家介绍一下简单用脚本定义数据来控制我们的游戏运作

#ifndef _GAME_SCRIPT_H_
#define _GAME_SCRIPT_H_

#include <vector>

class CGameScript
{
	//命令
	struct _COMMAND
	{
		int _time; //起始时间
		int _type; //类型
		int _radius; //半径
		int _x, _y; //起点
		int _dir; //方向：01234567表示周围八个方向
		int _speed; //速度
		int _step; //步数
		int _flag; //标志：0表示要消失，1表示不消失，2表示循环
	};
	std::vector<_COMMAND> m_Commands;

public:

	//物体
	struct _OBJECT
	{
		int type; //类型
		int radius; //半径
		int x, y; //位置
		int dir; //方向
		int speed; //速度
		int all_step; //总步数
		int cur_step; //当前步数
		int flag; //标志
	};

private:
	std::vector<_OBJECT> m_Objects;

	//时间
	int m_Time;

	//当前被触发的命令
	int m_CurCmd;

public:

	//加载脚本
	bool LoadScript(const char* fn);

	//重置时间
	void ResetTime();
	
	//系统运行
	void Run();

	//得到物体
	std::vector<_OBJECT>* GetObjects();
};

#endif