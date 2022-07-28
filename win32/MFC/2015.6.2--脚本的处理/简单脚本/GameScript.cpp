#include "GameScript.h"
#include <iostream>

bool CGameScript::LoadScript(const char* fn)
{
	//得到脚本文本

	//1：得到脚本初始内容
	FILE* pf = 0;
	fopen_s(&pf, fn, "rb");
	if (!pf)
		return false;
	fseek(pf, 0, SEEK_END);
	int fs = ftell(pf);
	rewind(pf);
	char* fd = new char[fs + 1];
	fd[fs] = 0;
	fread(fd, 1, fs, pf);
	fclose(pf);

	//2：整理脚本初始内容到新的字符串中
	char* buf = new char[fs + 1];
	int len = 0;
	for (int i = 0; i < fs; ++i)
	{
		//可见字符
		if (fd[i] > ' ')
			buf[len++] = fd[i];
	}
	buf[len] = 0;
	delete [] fd;

	//装载命令

	//1：得到命令的数量
	int command_num = 0;
	for (int i = 0; i < len; ++i)
	{
		if (buf[i] == ')')
			command_num += 1;
	}

	//2：循环加载
	m_Commands.clear();
	char* p = buf;
	char* p0, * p1;
	for (int i = 0; i < command_num; ++i)
	{
		_COMMAND command;

		//得到时间
		p0 = strchr(p, '(');
		p1 = strchr(p0, ',');
		*p1 = 0;
		command._time = atoi(p0 + 1);

		//得到类型
		p0 = p1 + 1;
		p1 = strchr(p0, ',');
		*p1 = 0;
		command._type = atoi(p0);

		//得到半径
		p0 = p1 + 1;
		p1 = strchr(p0, ',');
		*p1 = 0;
		command._radius = atoi(p0);

		//得到起点
		p0 = p1 + 2;
		p1 = strchr(p0, ',');
		*p1 = 0;
		command._x = atoi(p0);
		p0 = p1 + 1;
		p1 = strchr(p0, '>');
		*p1 = 0;
		command._y = atoi(p0);

		//得到方向
		p0 = p1 + 2;
		p1 = strchr(p0, ',');
		*p1 = 0;
		command._dir = atoi(p0);

		//得到速度
		p0 = p1 + 1;
		p1 = strchr(p0, ',');
		*p1 = 0;
		command._speed = atoi(p0);

		//得到步数
		p0 = p1 + 1;
		p1 = strchr(p0, ',');
		*p1 = 0;
		command._step = atoi(p0);

		//得到标志
		p0 = p1 + 1;
		p1 = strchr(p0, ')');
		*p1 = 0;
		command._flag = atoi(p0);

		//更新起始地址
		p = p1 + 1;

		//装入表中
		m_Commands.push_back(command);
	}

	//命令排序
	for (int i = (int)m_Commands.size() - 1; i > 0; --i)
	{
		for (int j = 0; j < i; ++j)
		{
			if (m_Commands[j]._time > m_Commands[j + 1]._time)
			{
				_COMMAND c = m_Commands[j];
				m_Commands[j] = m_Commands[j + 1];
				m_Commands[j + 1] = c;
			}
		}
	}

	return true;
}

void CGameScript::ResetTime()
{
	m_Time = 0;
	m_CurCmd = 0;
}

void CGameScript::Run()
{
	//移动物体
	for (std::vector<_OBJECT>::iterator it = m_Objects.begin(); it != m_Objects.end(); )
	{
		//移动结束
		if (it->cur_step == 0)
		{
			if (0 == it->flag)
				it = m_Objects.erase(it);
			else if (1 == it->flag)
				++it;
			else if (2 == it->flag)
			{
				it->cur_step = it->all_step;
				static const int change_dir[] = {4,5,6,7,0,1,2,3};
				it->dir = change_dir[it->dir];
				++it;
			}
		}
		//还在移动
		else
		{
			//701
			//6 2
			//543
			static const int offsetx[] = {0,1,1,1,0,-1,-1,-1};
			static const int offsety[] = {-1,-1,0,1,1,1,0,-1};
			it->x += offsetx[it->dir] * it->speed;
			it->y += offsety[it->dir] * it->speed;
			it->cur_step -= 1;
			++it;
		}
	}

	//创建物体
	while (m_CurCmd < (int)m_Commands.size() && m_Time == m_Commands[m_CurCmd]._time)
	{
		_OBJECT obj
			=
		{
			m_Commands[m_CurCmd]._type,
			m_Commands[m_CurCmd]._radius,
			m_Commands[m_CurCmd]._x,
			m_Commands[m_CurCmd]._y,
			m_Commands[m_CurCmd]._dir,
			m_Commands[m_CurCmd]._speed,
			m_Commands[m_CurCmd]._step,
			m_Commands[m_CurCmd]._step,
			m_Commands[m_CurCmd]._flag
		};

		//装入表中
		m_Objects.push_back(obj);

		//当前被触发的命令递增
		m_CurCmd += 1;
	}
	
	//时间递增
	m_Time += 1;
}

std::vector<CGameScript::_OBJECT>* CGameScript::GetObjects()
{
	return &m_Objects;
}