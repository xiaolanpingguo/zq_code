#ifndef _MEMORY_POOL_H_
#define _MEMORY_POOL_H_

class CMemoryPool
{
	struct NODE
	{
		NODE* pre; //前序指针
		NODE* next; //后序指针
		short head; //头部标志
		short use; //使用标志
		int size; //内存块大小
	};
	int m_CurSize; //最后内存块大小
	NODE* m_First; //首节点

	//拷贝构造和同类赋值设置为私有
	CMemoryPool(const CMemoryPool& that);
	CMemoryPool& operator = (const CMemoryPool& that);

public:

	CMemoryPool(int Size = 1024 * 1024 * 4);
	~CMemoryPool();

	void* Allocate(int Size);
	void Free(void* Mem);
};

#endif