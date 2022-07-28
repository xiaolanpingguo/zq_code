//集合专门用来做查找工作
//集合的本质是一个排好序的顺序表
//集合中不允许有重复的数据

#ifndef _SET_H_
#define _SET_H_

#define SDATA int

typedef struct _SET
{
	bool (*smaller)(SDATA,SDATA);
	int size;
	int length;
	SDATA* data;
}* SET;

//创建(容量)
SET createSET(bool (*smaller)(SDATA,SDATA),int size = 8);
//销毁(集合)
void destorySET(SET set);
//插入(集合，数据)
bool insertSET(SET set,SDATA data);
//删除(集合，数据)
bool eraseSET(SET set,SDATA data);
//查找(集合，数据)
SDATA* findSET(SET set,SDATA data);

#endif