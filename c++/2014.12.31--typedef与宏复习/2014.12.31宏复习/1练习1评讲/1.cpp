#include<iostream>

struct STUDENT
{
	int id;
	char name[32];
	int age;
};

void sortStu1(STUDENT* p,int num,int sel)
{
	if(1 == sel)
	{
		for(int i = num - 1; i > 0;--i)
		{
			for(int j = 0;j < i;++j)
			{
				if(p[j].id > p[j+1].id)
				{
					STUDENT a = p[j];
					p[j] = p[j+1];
					p[j+1] = a;
				}
			}
		}
	}
	else if(2 == sel)
	{
		for(int i = num - 1; i > 0;--i)
		{
			for(int j = 0;j < i;++j)
			{
				if(strcmp(p[j].name ,p[j+1].name) == 1)
				{
					STUDENT a = p[j];
					p[j] = p[j+1];
					p[j+1] = a;
				}
			}
		}
	}
	else if(3 == sel)
	{
		for(int i = num - 1; i > 0;--i)
		{
			for(int j = 0;j < i;++j)
			{
				if(p[j].age > p[j+1].age)
				{
					STUDENT a = p[j];
					p[j] = p[j+1];
					p[j+1] = a;
				}
			}
		}
	}

}


bool bigger_id(STUDENT s1,STUDENT s2)
{
	return s1.id > s2.id;
}

bool bigger_name(STUDENT s1,STUDENT s2)
{
	return strcmp(s1.name,s2.name);
}

bool bigger_age(STUDENT s1,STUDENT s2)
{
	return s1.age > s2.age;
}

void sortStu2(STUDENT* p,int num,bool (*bigger)(STUDENT,STUDENT))
{
	for(int i = num - 1; i > 0;--i)
	{
		for(int j = 0;j < i;++j)
		{
			if((*bigger)(p[j],p[j + 1]))
			{
				STUDENT a = p[j];
				p[j] = p[j+1];
				p[j+1] = a;
			}
		}
	}
}
void main()
{
	int  num;
	std::cin>>num;
	STUDENT* p = (STUDENT*)malloc(sizeof(STUDENT)*num);
	for(int i = 0; i < num;++i)
	{
		std::cin>>p[i].id>>p[i].name>>p[i].age;
	}
	int sel;
	do
	{
		std::cin>>sel;
	}while(sel < 1 || sel > 3);

	//sortStu1(p,num,sel);

	bool (*bigger[])(STUDENT,STUDENT)
	=
	{
		bigger_id,
		bigger_name,
		bigger_age
	};

	sortStu2(p,num,bigger[sel - 1]);
	
	for(int i = 0; i < num;++i)
	{
		std::cout<<p[i].id<<"  "<<p[i].name<<"  "<<p[i].age<<std::endl;
	}
	system("pause");
}