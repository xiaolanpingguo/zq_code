#include <iostream>
#include "FileData.h"

void GetIDPasswordFromFile(const char* fn, std::map<std::string, _PLAYER>* m)
{
	//账号数量(n)
	//账号0、密码0
	//账号1、密码1
	//...
	//账号n、密码n

	FILE* pf = 0;
	fopen_s(&pf, fn, "rb");

	//如果没有文件就新建文件
	if (!pf)
	{
		fopen_s(&pf, fn, "wb");
		fclose(pf);
		m->clear();
		return;
	}

	//读取文件内容
	fseek(pf, 0, SEEK_END);
	int fs = ftell(pf);
	rewind(pf);
	char* fd = (char*)malloc(fs);
	fread(fd, 1, fs, pf);
	fclose(pf);

	//得到数量
	int num = *((int*)fd);

	//得到所有玩家信息
	char* p = fd + 4;
	for (int i = 0; i < num; ++i)
	{
		std::string id = p;
		p += strlen(p) + 1;
		std::string name = p;
		p += strlen(p) + 1;
		std::string pw = p;
		p += strlen(p) + 1;
		
		int face = *((int*)p);
		p += sizeof(int);
		int score = *((int*)p);
		p += sizeof(int);
		int win = *((int*)p);
		p += sizeof(int);
		int lose = *((int*)p);
		p += sizeof(int);
		int draw = *((int*)p);
		p += sizeof(int);

		_PLAYER player = {INVALID_SOCKET,id,name,pw,face,score,win,lose,draw,-1,-1,_PS_NONE};
		m->insert(std::pair<std::string, _PLAYER>(id, player));
	}

	//释放
	free(fd);
}

void SaveFile(const char* fn, std::map<std::string, _PLAYER>* m)
{
	FILE* pf = 0;
	fopen_s(&pf, fn, "wb");

	int num = (int)m->size();
	fwrite(&num, 1, 4, pf);

	std::map<std::string, _PLAYER>::iterator it;
	for (it = m->begin(); it != m->end(); ++it)
	{
		fwrite(it->second.m_ID.c_str(), 1, it->second.m_ID.length() + 1, pf);
		fwrite(it->second.m_Name.c_str(), 1, it->second.m_Name.length() + 1, pf);
		fwrite(it->second.m_Password.c_str(), 1, it->second.m_Password.length() + 1, pf);
		fwrite(&it->second.m_Face,1,sizeof(int),pf);
		fwrite(&it->second.m_Score,1,sizeof(int),pf);
		fwrite(&it->second.m_Win,1,sizeof(int),pf);
		fwrite(&it->second.m_Lose,1,sizeof(int),pf);
		fwrite(&it->second.m_Draw,1,sizeof(int),pf);
	}

	fclose(pf);
}