#include"map.h"

CMap::CMap()
{
	for(int i=0;i<MAP_S;i++)
	{
		map[i]=_KD;
	}
}
void CMap::SetMap(int pos,int q)
{
	map[pos] =q;
}
int CMap::GetMap(int pos)
{
	return map[pos];
}
void CMap::SetCp(CWzq * cp)
{
	m_cp = cp ;
}
CWzq* CMap::GetCp()
{
	return m_cp;
}

char* CMap::GetMapdz()
{
	return map;
}

void CMap::CleanMap()
{
	for(int i=0;i<MAP_S;i++)
	{
		map[i]=_KD;
	}
}
