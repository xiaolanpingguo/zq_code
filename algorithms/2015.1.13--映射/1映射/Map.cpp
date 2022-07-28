#include"Map.h"
#include <iostream>

//´´½¨(ÈÝÁ¿)
MAP createMAP(bool (*smaller)(MKEY,MKEY),int size)
{
	MAP map = (MAP)malloc(sizeof(_MAP));
	map->smaller = smaller;
	map->size = size;
	map->length = 0;
	map->key = (MKEY*)malloc(sizeof(MKEY) * map->size);
	map->data = (MDATA*)malloc(sizeof(MDATA)* map->size);
	return map;
}
//Ïú»Ù(Ó³Éä)
void destoryMAP(MAP map)
{
	free(map->key);
	free(map->data);
	free(map);
}
//²åÈë(Ó³Éä£¬¼üÖµ£¬Êý¾Ý)
bool insertMAP(MAP map,MKEY key,MDATA data)
{
	int begin = 0,end = map->length - 1;
	while(begin <= end)
	{
		int half = (begin + end) / 2;
		if((*map->smaller)(key,map->key[half]))
			end = half - 1;
		else if((*map->smaller)(map->key[half],key))
			begin = half + 1;
		else
			return false;
	}

	if(map->length == map->size)
	{
		map->size *= 2;
		MKEY* pKey = (MKEY*)malloc(sizeof(MKEY) * map->size);
		MDATA* pData = (MDATA*)malloc(sizeof(MDATA)* map->size);
		for(int i = 0; i < map->length;++i)
		{
			pKey[i] = map->key[i];
			pData[i] = map->data[i];
		}
		free(map->key);
		free(map->data);
		map->key = pKey;
		map->data = pData;
	}

	int move = map->length - begin;
	for(int i = 0; i < move;++i)
	{
		map->data[map->length - i] = map->data[map->length - i - 1];
		map->key[map->length - i] = map->key[map->length - i - 1];
	}
	map->key[begin] = key;
	map->data[begin] = data;
	map->length += 1;
	return true;
}
//É¾³ý(Ó³Éä£¬¼üÖµ)
bool eraseMAP(MAP map,MKEY key)
{
	int begin = 0,end = map->length - 1;
	while(begin <= end)
	{
		int half = (begin + end) / 2;
		if((*map->smaller)(key,map->key[half]))
			end = half - 1;
		else if((*map->smaller)(map->key[half],key))
			begin = half + 1;
		else
		{
			int move = map->length - half - 1;
			for(int i = 0; i < move;++i)
			{
				map->key[half + i] = map->key[half + i + 1];
				map->data[half + i] = map->data[half + i + 1];
			}
			map->length -= 1;
			return true;
		}
	}
	return false;
}
//²éÕÒ(Ó³Éä£¬¼üÖµ)
MDATA* findMAP(MAP map,MKEY key)
{
	int begin = 0,end = map->length - 1;
	while(begin <= end)
	{
		int half = (begin + end) / 2;
		if((*map->smaller)(key,map->key[half]))
			end = half - 1;
		else if((*map->smaller)(map->key[half],key))
			begin = half + 1;
		else
		{
			return &map->data[half];
		}
	}
	return 0;
}