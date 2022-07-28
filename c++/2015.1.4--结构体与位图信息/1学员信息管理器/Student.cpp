#include "Student.h"
#include <iostream>
int size;
int len;
_STUDENT* stu;

void Init()
{
	size = 8;
	len = 0;
	stu = (_STUDENT*)malloc(sizeof(_STUDENT) * size);
}

void Add(_STUDENT s)
{
	if(len == size)
	{
		size *= 2;
		_STUDENT* p = (_STUDENT*)malloc(sizeof(_STUDENT) * size);
		for(int i = 0;i < len;++i)
			p[i] = stu[i];
		free(stu);
		stu = p;
	}
	stu[len++] = s;
}

bool Erase(int i)
{
	if(i < 0 || i >= len)
		return false;
	int m = len - i - 1;
	for(int j = 0; j < m;++j)
		stu[i + j] = stu[i + j + 1];
	len--;
	return true;
}

void End()
{
	free(stu);
}