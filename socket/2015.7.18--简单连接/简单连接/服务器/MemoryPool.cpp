#include "MemoryPool.h"
#include <iostream>

#define _NO_HEAD 0 //非头节点
#define _IS_HEAD 1 //头节点
#define _NO_USE 0 //未使用
#define _IN_USE 1 //使用

CMemoryPool::CMemoryPool(const CMemoryPool& that)
{}
CMemoryPool& CMemoryPool::operator = (const CMemoryPool& that)
{return *this;}

CMemoryPool::CMemoryPool(int Size)
:
m_CurSize(Size),
m_First((NODE*)malloc(m_CurSize))
{
	m_First->pre = 0;
	m_First->next = 0;
	m_First->head = _IS_HEAD;
	m_First->use = _NO_USE;
	m_First->size = m_CurSize - sizeof(NODE);
}

CMemoryPool::~CMemoryPool()
{
	NODE* p = m_First;
	while (p)
	{
		NODE* q = p->next;
		while (q && q->head == _NO_HEAD)
			q = q->next;

		free(p);

		p = q;
	}
}

void* CMemoryPool::Allocate(int Size)
{
	NODE* p, * last;
	for (p = m_First; p; p = p->next)
	{
		last = p;
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
		q->head = _NO_HEAD;
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
	{
		//分配新内存块
		m_CurSize = m_CurSize * 2 + Size;
		NODE* r = (NODE*)malloc(m_CurSize);

		//设置新内存块
		r->pre = last;
		r->next = 0;
		r->head = _IS_HEAD;
		r->use = _NO_USE;
		r->size = m_CurSize - sizeof(NODE);

		//设置新内存块的前序节点
		last->next = r;

		//分配外部需要的内存
		NODE* q = (NODE*)((char*)r + r->size - Size);

		//设置新节点
		q->pre = r;
		q->next = r->next;
		q->head = _NO_HEAD;
		q->use = _IN_USE;
		q->size = Size;

		//设置新节点的前序节点
		r->next = q;
		r->size -= sizeof(NODE) + Size;

		return q + 1;
	}
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

		//讨论前序节点，前序节点一定是有的且一定和释放节点是连在一起的
		NODE* pre = p->pre;

		//如果前序节点没有使用，就要将当前释放节点与前序节点进行合并
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

		//讨论后序节点，后序节点不一定是有的，就算有
		//也有可能是内存块的头部节点
		NODE* next = p->next;

		//如果有后序节点，且后序节点没有使用，就要将当前释
		//放节点与后序节点进行合并
		if (next && next->use == _NO_USE && next->head == _NO_HEAD)
		{
			//有可能为0，也有可能不为0
			p->next = next->next;
			p->size += next->size + sizeof(NODE);
			if (p->next)
				p->next->pre = p;
		}
	}
}