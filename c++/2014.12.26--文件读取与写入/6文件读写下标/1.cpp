#include<iostream>


void main()
{
	FILE* pf = 0;

	fopen_s(&pf,"存储1.txt","rb");
	
	if(!pf)
	{
		std::cout<<"指定文件无法打开,";
		system("pause");
		return;
	}

	//得到文件的大小

	//1：移动文件读写下标
	//01)文件指针
	//02)移动的偏移量
	//03)移动的目的地
	//SEEK_CUR:表示当前位置
	//SEEK_END:表示文件末尾
	//SEEK_SET:表示文件开头
	fseek(pf,0,SEEK_END);
	//2：得到当前读写下标距离文件开头位置的字节数
	int filesize = ftell(pf);
	//移动读写下标到文件开头
	rewind(pf);//完全等同于fseek(pf,0,SEEK_SET);

	fseek(pf,6,SEEK_CUR);

	int cs = ftell(pf);

	fseek(pf,-1,SEEK_CUR);

	cs = ftell(pf);
	//rewind(pf);
	fseek(pf,0,SEEK_SET);
	cs = ftell(pf);

	fclose(pf);
	system("pause");
}