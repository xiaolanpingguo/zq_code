#include "SqList.h"
#include <iostream>

//创建(容量)
SQLIST createSQLIST(int size)
{
	SQLIST sqlist = (SQLIST)malloc(sizeof(_SQ_LIST));
	sqlist->size = size;
	sqlist->length = 0;
	sqlist->data  =  (SLDATA*)malloc(sizeof(SLDATA)* sqlist->size);
	return sqlist;
}
//销毁(顺序表)
void destroySQLIST(SQLIST sqlist)
{
	free(sqlist->data);
	free(sqlist);
}
//插入(顺序表，数据，位置)
bool insertSQLIST(SQLIST sqlist,SLDATA data,int pos)
{
	if(pos < 0 || pos > sqlist->length)
		return false;

	if(sqlist->length == sqlist->size)
	{
		sqlist->size *= 2;
		SLDATA* p = (SLDATA*)malloc(sizeof(SLDATA) * sqlist->size);
		for(int i = 0; i < sqlist->length;++i)
			p[i] = sqlist->data[i];
		free(sqlist->data);
		sqlist->data = p;
	}

	int move = sqlist->length - pos;
	for(int i = 0; i < move; ++i)
		sqlist->data[sqlist->length - i] = sqlist->data[sqlist->length - i - 1];
	sqlist->data[pos] = data;
	sqlist->length ++;
	return true;
}
//推入(顺序表，数据)
void pushSQLIST(SQLIST sqlist,SLDATA data)
{
	insertSQLIST(sqlist,data,sqlist->length);
}
//删除(顺序表，位置)
bool eraseSQLIST(SQLIST sqlist,int pos)
{
	if(pos < 0 || pos >= sqlist->length)
		return  false;
	int move = sqlist->length - pos - 1;
	for(int i = 0; i < move;++i)
		sqlist->data[pos + i] = sqlist->data[pos + i + 1];
	sqlist->length -= 1;
	return true;
}
//清空(顺序表)
void clearSQLIST(SQLIST sqlist)
{
	sqlist->length = 0;
}
//长度(顺序表)
int lengthSQLIST(SQLIST sqlist)
{
	return sqlist->length;
}
//获取(顺序表，位置)
SLDATA* getSQLIST(SQLIST sqlist,int pos)
{
	if(pos < 0 || pos > sqlist->length  - 1)
		return 0;
	return sqlist->data + pos;
}
//查找(顺序表，数据，起始位置，等于函数)
int findSQLIST(SQLIST sqlist,SLDATA data,int begin,bool (*equal)(SLDATA,SLDATA))
{
	if(begin < 0 || begin > sqlist->length - 1)
		return -2;
	for(;begin < sqlist->length;++begin)
	{
		if((*equal)(data,sqlist->data[begin]))
			return begin;
	}
	return -1;
}
//排序
void sortSQLIST(SQLIST sqlist,bool increase,bool (*greater)(SLDATA,SLDATA))
{
	if(increase)
	{
		for(int i = 0; i < sqlist->length - 1; ++i)
		{
			int j = i;
			for(int k = j + 1; k < sqlist->length; ++k)
			{
				if((*greater)(sqlist->data[j],sqlist->data[k]))
					j = k;
			}
			if(j != i)
			{
				SLDATA d = sqlist->data[j];
				sqlist->data[j] = sqlist->data[i];
				sqlist->data[i] = d;
			}
		}
	}
	else
	{
		for(int i = 0; i < sqlist->length - 1; ++i)
		{
			int j = i;
			for(int k = j + 1; k < sqlist->length; ++k)
			{
				if((*greater)(sqlist->data[k],sqlist->data[j]))
					j = k;
			}
			if(j != i)
			{
				SLDATA d = sqlist->data[j];
				sqlist->data[j] = sqlist->data[i];
				sqlist->data[i] = d;
			}
		}
	}
}
