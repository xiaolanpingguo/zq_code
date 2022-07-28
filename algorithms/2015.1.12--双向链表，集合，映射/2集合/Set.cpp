#include "Set.h"
#include <iostream>

//创建(容量)
SET createSET(bool (*smaller)(SDATA,SDATA),int size)
{
	SET set = (SET)malloc(sizeof(_SET));
	set->smaller = smaller;
	set->size = size;
	set->length = 0;
	set->data = (SDATA*)malloc(sizeof(SDATA) * set->size);
	return set;
}
//销毁(集合)
void destorySET(SET set)
{
	free(set->data);
	free(set);
}
//插入(集合，数据)
bool insertSET(SET set,SDATA data)
{
	//int pos = 0;
	//for(;pos<set->length;++pos)
	//{
	//	if(!(*set->smaller)(data,set->data[pos])
	//	&& !(*set->smaller)(set->data[pos],data))
	//		return false;
	//	else if((*set->smaller)(data,set->data[pos])
	//		break;
	//}
	int begin = 0, end = set->length - 1;
	while(begin <= end)
	{
		int half = (begin + end)/2;
		if((*set->smaller)(data,set->data[half]))
			end = half - 1;
		else if(!(*set->smaller)(set->data[half],data))
			begin = half + 1;
		else 
			return false;
	}

	if(set->length == set->size)
	{
		set->size *= 2;
		SDATA* p = (SDATA*)malloc(sizeof(SDATA) * set->size);
		for(int i = 0; i < set->length;++i)
			p[i] = set->data[i];
		free(set->data);
		set->data = p;
	}

	int move = set->length - begin;
	for(int i = 0; i < move;++i)
	{
		set->data[set->length - i] = set->data[set->length - 1 - i];
	}
	set->data[begin] = data;
	set->length++;
	return true;
}
//删除(集合，数据)
bool eraseSET(SET set,SDATA data)
{
	int begin = 0, end = set->length - 1;
	while(begin <= end)
	{
		int half = (begin + end)/2;
		if((*set->smaller)(data,set->data[half]))
			end = half - 1;
		else if(!(*set->smaller)(set->data[half],data))
			begin = half + 1;
		else 
		{
			int move = set->length - half - 1;
			for(int i = 0; i < move;++i)
			{
				set->data[half + i] = set->data[half + i + 1];
			}
			set->length--;
			return true;
		}
	}
	return false;
}
//查找(集合，数据)
SDATA* findSET(SET set,SDATA data)
{
	int begin = 0, end = set->length - 1;
	while(begin <= end)
	{
		int half = (begin + end)/2;
		if((*set->smaller)(data,set->data[half]))
			end = half - 1;
		else if(!(*set->smaller)(set->data[half],data))
			begin = half + 1;
		else 
		{
			return &set->data[half];
		}
	}
	return 0;
}