#ifndef _SQLIST_H_
#define _SQLIST_H_

#define SLDATA int

typedef struct _SQ_LIST
{
	int size;//容量
	int length;//长度
	SLDATA* data;//数据
}* SQLIST;

//创建(容量)
SQLIST createSQLIST(int size = 8);
//销毁(顺序表)
void destroySQLIST(SQLIST sqlist);
//插入(顺序表，数据，位置)
bool insertSQLIST(SQLIST sqlist,SLDATA data,int pos);
//推入(顺序表，数据)
void pushSQLIST(SQLIST sqlist,SLDATA data);
//删除(顺序表，位置)
bool eraseSQLIST(SQLIST sqlist,int pos);
//清空(顺序表)
void clearSQLIST(SQLIST sqlist);
//长度(顺序表)
int lengthSQLIST(SQLIST sqlist);
//获取(顺序表，位置)
SLDATA* getSQLIST(SQLIST sqlist,int pos);
//查找(顺序表，数据，起始位置，等于函数)
int findSQLIST(SQLIST sqlist,SLDATA data,int begin,bool (*equal)(SLDATA,SLDATA));
//排序
void sortSQLIST(SQLIST sqlist,bool increase,bool (*greater)(SLDATA,SLDATA));


#endif