#ifndef _MEMORY_POOL_H_
#define _MEMORY_POOL_H_

//凡是存储器，都有可能出现存储器中的“碎片”，所谓“碎片”
//指的是繁多的，小块的存储单元，这些存储单元一多，那么将
//导致操作系统要希望分配大的内存块要进行很多的处理工作，
//也就是使得整体的系统效率变慢，如果在程序中快速的、大量的
//分配（malloc、new、new []）和释放堆内存（free、delete、
//delete []）就会造成内存碎片，久而久之就使得系统变慢，解决
//这一个问题的思路是提前预备一个较大的内存块，要使用的时候
//从这个内存块中取一块出去使用，要回收的时候再将内存块还原
//即可，这样的实现就是内存池

class CMemoryPool
{
	struct NODE
	{
		NODE* pre; //前序指针
		NODE* next; //后序指针
		int use; //使用标志
		int size; //内存块大小
	};
	NODE* m_First; //首节点

public:

	CMemoryPool(int Size = 1024 * 1024 * 4);
	~CMemoryPool();

	void* Allocate(int Size);
	void Free(void* Mem);
};

#endif