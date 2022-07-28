#ifndef _TEST_H_
#define _TEST_H_

class CObject;

//运行时类别结构体，所有的MFC类都通过宏
//来自带一个这个结构体静态对象
struct _RUNTIME_CLASS
{
	char* name;
	CObject* (* create)();
	_RUNTIME_CLASS* parent_class;
	_RUNTIME_CLASS* next_class;
	static _RUNTIME_CLASS* first_class;

	static CObject* createClass(const char* name);
};

class CObject
{
public:
	virtual ~CObject(){}
	static _RUNTIME_CLASS CObjectRuntimeClass;
	static CObject* createCObject();
	bool IsKindOf(const char*);
};

#define _DECLEAR_CLASS(classname) \
public: \
	static _RUNTIME_CLASS classname##RuntimeClass; \
	static CObject* create##classname##RuntimeClass(); \
	bool IsKindOf(const char*);
	

//本类是用来构造_RUNTIME_CLASS的链表结构的
class Init
{
public:
	Init(_RUNTIME_CLASS* rc)
	{
		_RUNTIME_CLASS* p = _RUNTIME_CLASS::first_class;
		while (p->next_class)
			p = p->next_class;
		p->next_class = rc;
	}
};

#define _DEFINE_CLASS(classname, parentname) \
	_RUNTIME_CLASS classname##::classname##RuntimeClass = {#classname, classname::##create##classname##RuntimeClass, &parentname##::parentname##RuntimeClass, 0}; \
Init classname##Init(&classname##::classname##RuntimeClass); \
CObject* classname::##create##classname##RuntimeClass() \
{ \
	return new classname; \
} \
bool classname##::IsKindOf(const char* name) \
{ \
	_RUNTIME_CLASS* p = &classname##RuntimeClass; \
	while (p) \
	{ \
		if (strcmp(p->name, name) == 0) \
			return true; \
		else \
			p = p->parent_class; \
	} \
	return false; \
}

#include <iostream>

class A : public CObject
{
	_DECLEAR_CLASS(A)

//public:
//	static _RUNTIME_CLASS ARuntimeClass;
//	bool IsKindOf(const char*);

public:
	A(){std::cout<<"A构造"<<std::endl;}
	~A(){std::cout<<"A析构"<<std::endl;}
};

class B : public A
{
	_DECLEAR_CLASS(B)
public:
	B(){std::cout<<"B构造"<<std::endl;}
	~B(){std::cout<<"B析构"<<std::endl;}
};

class C : public A
{
	_DECLEAR_CLASS(C)
public:
	C(){std::cout<<"C构造"<<std::endl;}
	~C(){std::cout<<"C析构"<<std::endl;}
};

#endif

//《深入浅出MFC》侯捷
//运行时刻类型识别、动态生成等功能在更高层次的
//语言中很多都被语言直接支持，比如Java、C#、ObjectiveC