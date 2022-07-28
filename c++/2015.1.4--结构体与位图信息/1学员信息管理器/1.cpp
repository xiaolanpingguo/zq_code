#include<iostream>
#include "Student.h"
void bc1()
{
	char fn[256];
	std::cin>>fn;
	FILE* pf = 0;
	fopen_s(&pf,fn,"wb");
	fwrite(stu,len,sizeof(_STUDENT),pf);

	//fwrite(&len,1,sizeof(int),pf);
	//for(int i = 0; i < len ; ++i)
	//{
	//	fwrite(&stu[i].id,1,sizeof(int),pf);
	//	fwrite(&stu[i].name,1,strlen(stu[i].name) + 1,pf);
	//	fwrite(&stu[i].age,1,sizeof(int),pf);
	//}
	fclose(pf);
	std::cout<<"±£´æ³É¹¦";
	system("pause");
}

void dq1()
{
	char fn[256];
	std::cin>>fn;
	FILE* pf = 0;
	fopen_s(&pf,fn,"rb");
	if(!pf)
		return;
	fseek(pf,0,SEEK_END);
	int fs = ftell(pf);
	rewind(pf);

	_STUDENT *p = (_STUDENT*)malloc(fs);
	fread(p,1,fs,pf);
	fclose(pf);
	int n = fs / sizeof(_STUDENT);
	for(int i = 0; i < n;++i)
		std::cout<<i<<"  "<<p[i].id<<"  "<<p[i].name<<"  "<<p[i].age<<std::endl;
	system("pause");
	free(p);
}

void xie()
{
	Init();
	while(1)
	{
		system("cls");
		for(int i = 0; i < len;++i)
			std::cout<<i<<"  "<<stu[i].id<<"  "<<stu[i].name<<"  "<<stu[i].age<<std::endl;
		std::cout<<"1)Ìí¼Ó\n2)É¾³ý\n3)±£´æ\n4)·µ»Ø\nÇëÑ¡Ôñ";
		int sel;
		std::cin>>sel;
		if(1 == sel)
		{
			_STUDENT s;
			std::cin>>s.id>>s.name>>s.age;
			Add(s);
			std::cout<<"Ìí¼Ó³É¹¦";
			system("pause");
		}
		else if(2 == sel)
		{
			int ei;
			std::cin>>ei;
			if(Erase(ei))
				std::cout<<"É¾³ý³É¹¦";
			else
				std::cout<<"É¾³ýÊ§°Ü";
			system("pause");
		}
		else if(3 == sel)
		{
			bc1();
		}
		else if(4 == sel)
		{
			break;
		}
	}
	End();
}

void main()
{
	while(1)
	{
		system("cls");
		std::cout<<"1)Ð´\n2)¶Á\n3)ÍË\nÇëÑ¡Ôñ";
		int sel;
		std::cin>>sel;
		if(1 == sel)
			xie();
		else if(2 == sel)
			dq1();
		else if(3 == sel)
			break;
	}
	system("pause");
}