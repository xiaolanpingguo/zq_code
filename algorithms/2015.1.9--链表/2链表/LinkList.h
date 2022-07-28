#ifndef _LINK_LIST_H_
#define _LINK_LIST_H_
#define LLDATA int

typedef struct _LINK_LIST
{
	LLDATA data;//数据
	_LINK_LIST* next;//指向下一个节点的指针
}* LINKLIST;

//创建
LINKLIST createLINKLIST();
//销毁(链表)
void destroyLINKLIST(LINKLIST linklist);
//插入(链表，数据，位置)
bool insertLINKLIST(LINKLIST linklist,LLDATA data,int pos);
//推入(链表，数据)
void pushLINKLIST(LINKLIST linklist,LLDATA data);
//删除(链表，位置)
bool eraseLINKLIST(LINKLIST linklist,int pos);
//清空(链表)
void clearLINKLIST(LINKLIST linklist);
//长度(链表)
int lengthLINKLIST(LINKLIST linklist);
//获取(链表，位置)
LLDATA* getLINKLIST(LINKLIST linklist,int pos);
//查找(链表，数据，开始位置，相等函数)
int findLINKLIST(LINKLIST linklist,LLDATA data,int begin, bool (*equal)(LLDATA,LLDATA));
//排序
void sortLINKLIST(LINKLIST linklist,bool increase,bool (*greater)(LLDATA,LLDATA));
#endif