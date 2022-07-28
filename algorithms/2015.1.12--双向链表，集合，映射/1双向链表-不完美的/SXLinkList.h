#ifndef _SX_LINK_LIST_H_
#define _SX_LINK_LIST_H_
#define LLDATA int

typedef struct _SXLINK_LIST
{
	LLDATA data;//数据
	_SXLINK_LIST* next;//指向下一个节点的指针
	_SXLINK_LIST* pre;//指向前面一个节点的指针
}* SXLINKLIST;

//创建
SXLINKLIST createSXLINKLIST();
//销毁(链表)
void destroySXLINKLIST(SXLINKLIST sxlinklist);
//插入(链表，数据，位置)
bool insertSXLINKLIST(SXLINKLIST sxlinklist,LLDATA data,int pos);
//推入(链表，数据)
void pushSXLINKLIST(SXLINKLIST sxlinklist,LLDATA data);
//删除(链表，位置)
bool eraseSXLINKLIST(SXLINKLIST sxlinklist,int pos);
//清空(链表)
void clearSXLINKLIST(SXLINKLIST sxlinklist);
//长度(链表)
int lengthSXLINKLIST(SXLINKLIST sxlinklist);
//获取(链表，位置)
LLDATA* getSXLINKLIST(SXLINKLIST sxlinklist,int pos);
//查找(链表，数据，开始位置，相等函数)
int findSXLINKLIST(SXLINKLIST sxlinklist,LLDATA data,int begin, bool (*equal)(LLDATA,LLDATA));
//排序
void sortSXLINKLIST(SXLINKLIST sxlinklist,bool increase,bool (*greater)(LLDATA,LLDATA));
#endif