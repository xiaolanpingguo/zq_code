#ifndef _MAP_
#define _MAP_

#include"wzq.h"

#define MAP_W 20
#define MAP_H 20
#define MAP_S MAP_W*MAP_H

#define _KD 0
#define _HQ 1
#define _BQ 2


class CMap
{
	char map[MAP_S];
	CWzq* m_cp;
public:
	CMap();
	void SetMap(int pos,int q);
	int GetMap(int pos);
	void SetCp(CWzq* cp);
	CWzq* GetCp();
	//得到地图数组的首地址
	char* GetMapdz();
	void CleanMap();
	
};

#endif