//映射专门用来做查找工作,是根据KEY值去查找DATA
//映射的本质是一个根据KEY值排好序的顺序表
//映射中不允许有重复的KEY值，可以有重复的数据

#ifndef _MAP_H_
#define _MAP_H_

#define MKEY int
#define MDATA char*

typedef struct _MAP
{
	bool (*smaller)(MKEY,MKEY);
	int size;
	int length;
	MKEY* key;
	MDATA* data;
}* MAP;

//创建(容量)
MAP createMAP(bool (*smaller)(MKEY,MKEY),int size = 8);
//销毁(映射)
void destoryMAP(MAP map);
//插入(映射，键值，数据)
bool insertMAP(MAP map,MKEY key,MDATA data);
//删除(映射，键值)
bool eraseMAP(MAP map,MKEY key);
//查找(映射，键值)
MDATA* findMAP(MAP map,MKEY key);

#endif