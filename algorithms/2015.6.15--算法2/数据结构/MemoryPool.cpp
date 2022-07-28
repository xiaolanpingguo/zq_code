#include "MemoryPool.h"
#include <iostream>

#define _NO_USE 0
#define _IN_USE 1

CMemoryPool::CMemoryPool(int Size)
:
m_First((NODE*)malloc(Size))
{
	m_First->pre = 0;
	m_First->next = 0;
	m_First->use = _NO_USE;
	m_First->size = Size - sizeof(NODE);
}

CMemoryPool::~CMemoryPool()
{
	free(m_First);
}

void* CMemoryPool::Allocate(int Size)
{
	NODE* p;
	for (p = m_First; p; p = p->next)
	{
		if (p->use == _NO_USE && p->size >= Size + (int)sizeof(NODE))
			break;
	}

	if (p)
	{
		//得到分配的内存块节点地址
		//NODE* q = (char*)p + sizeof(NODE) + p->size - Size - sizeof(NODE);
		NODE* q = (NODE*)((char*)p + p->size - Size);

		//设置新节点
		q->pre = p;
		q->next = p->next;
		q->use = _IN_USE;
		q->size = Size;

		//设置新节点的前序节点
		p->next = q;
		p->size -= sizeof(NODE) + Size;

		//设置新节点的后序节点
		if (q->next)
			q->next->pre = q;

		return q + 1;
	}
	else
		return malloc(Size);
}

void CMemoryPool::Free(void* Mem)
{
	NODE* p;
	for (p = m_First; p; p = p->next)
	{
		if (p + 1 == Mem)
			break;
	}

	//是内存块中的地址
	if (p)
	{
		//无论是哪种情况，都要设置当前释放节点的使用为_NO_USE
		p->use = _NO_USE;

		//讨论前序节点，前序节点一定是有的
		NODE* pre = p->pre;

		//如果前序节点没有使用，就要将当前释放节点与前序
		//节点进行合并
		if (pre->use == _NO_USE)
		{
			//有可能为0，也有可能不为0
			pre->next = p->next;
			pre->size += p->size + sizeof(NODE);
			if (pre->next)
				pre->next->pre = pre;
			//更新p节点，目的是为了让p始终指向
			//p->next的前序节点
			p = pre;
		}

		//讨论后序节点，后序节点不一定是有的
		NODE* next = p->next;

		//如果有后序节点，且后序节点没有使用，就要将当前释
		//放节点与后序节点进行合并
		if (next && next->use == _NO_USE)
		{
			//有可能为0，也有可能不为0
			p->next = next->next;
			p->size += next->size + sizeof(NODE);
			if (p->next)
				p->next->pre = p;
		}
	}
	else
		free(Mem);
}