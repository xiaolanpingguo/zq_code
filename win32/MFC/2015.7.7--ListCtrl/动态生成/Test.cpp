#include "Test.h"
#include <iostream>

_RUNTIME_CLASS* _RUNTIME_CLASS::first_class = &CObject::CObjectRuntimeClass;
CObject* _RUNTIME_CLASS::createClass(const char* name)
{
	_RUNTIME_CLASS* p = first_class;
	while (p)
	{
		if (strcmp(p->name, name) == 0)
			return (*p->create)();
		else
			p = p->next_class;
	}
	return 0;
}
_RUNTIME_CLASS CObject::CObjectRuntimeClass = {"CObject", 0, 0};
CObject* CObject::createCObject()
{
	return new CObject;
}
bool CObject::IsKindOf(const char* name)
{
	return strcmp(name, CObjectRuntimeClass.name) == 0;
}


_DEFINE_CLASS(A, CObject)

//_RUNTIME_CLASS A::ARuntimeClass = {"A", &CObject::CObjectRuntimeClass, 0};
//Init AInit(&A::ARuntimeClass);
//bool A::IsKindOf(const char* name)
//{
//	_RUNTIME_CLASS* p = &ARuntimeClass;
//	while (p)
//	{
//		if (strcmp(p->name, name) == 0)
//			return true;
//		else
//			p = p->parent_class;
//	}
//	return false;
//}

_DEFINE_CLASS(B, A)
_DEFINE_CLASS(C, A)