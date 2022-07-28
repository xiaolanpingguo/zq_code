typedef struct _LINK_LIST
{
	int data;
	_LINK_LIST* next;
}* LINKLIST;

LINKLIST createLINKLIST()
{
	LINKLIST linklist = (LINKLIST)malloc(sizeof(_LINK_LIST));
	linklist->next = 0;
	return linklist;
}


LINKLIST CloneLINKLIST(LINKLIST linklist)
{
	//创建新的链表
	LINKLIST linklist1 = createLINKLIST();
	LINKLIST q = linklist1;
	for(LINKLIST p = linklist->next;p;p = p->next)
	{
		LINKLIST linklist2 = createLINKLIST();
		linklist2->data = p->data;
		q->next = linklist2;
		q = q->next;
	}
	return linklist1;
}

void inverseLINKLIST(LINKLIST linklist)
{
	if(!linklist->next || !linklist->next->next)
		return;
	LINKLIST p = linklist->next;
	LINKLIST q = p->next;

	while(q)
	{
		LINKLIST r = q->next;
		q->next = p;
		p = q;
		q = r;
	}
	linklist->next->next =  0;
	linklist->next = p;
}


bool isCircleLINKLIST(LINKLIST list)
{
	LINKLIST p = list->next;
	while(p)
	{
		LINKLIST q = list->next;
		for(q && q != p;q = q->next)
		{
			if(p ->next == q)
				return true;
		}
		p = p ->next;
	}
	return false;
}