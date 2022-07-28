#ifndef _LINK_LIST_H_
#define _LINK_LIST_H_

struct _BOX_STAGE
{
	char* m;
	int w,h;
	int x,y;
};


#define DATA _BOX_STAGE

typedef struct _NODE //节点
{
	DATA _d;
	_NODE* _n;
}* LinkList;

//链表的相关函数声明
LinkList CreateLinkList();
void DestroyLinkList(LinkList linklist);
int LengthLinkList(LinkList linklist);
bool InsertLinkList(LinkList linklist, DATA data,int pos);
void PushLinkList(LinkList linklist,DATA data);
bool EraseLinkList(LinkList linklist,int pos);
void ClearLinkList(LinkList linklist);
DATA* GetLinkList(LinkList linklist, int pos);
int LocateLinkList(LinkList linklist,int Begin,DATA data,bool (*_E)(DATA,DATA));
void SortLinkList(LinkList linklist, bool (*_B)(DATA,DATA),bool increase = true);



#endif