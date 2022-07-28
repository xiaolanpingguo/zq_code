#ifndef _STUDENT_H_
#define _STUDENT_H_

struct _STUDENT
{
	int id;
	char name[32];
	int age;
};

extern int len;
extern _STUDENT* stu;
void Init();
void Add(_STUDENT s);
bool Erase(int i);
void End();

#endif