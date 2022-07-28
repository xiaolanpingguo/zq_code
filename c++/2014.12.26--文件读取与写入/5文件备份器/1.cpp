#include<iostream>


void main()
{

	std::cout<<"请输入要备份的源文件路径:";
	char filename[256];
	std::cin>>filename;

	FILE* pf = 0;

	fopen_s(&pf,filename,"rb");
	
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
	
	//开辟内存空间
	char* filedata = (char*)malloc(filesize);
	
	//将文件内容读入到内存中
	fread(filedata,1,filesize,pf);

	//关闭文件
	fclose(pf);

	//输入备份文件路径
	std::cout<<"请输入要备份的目标文件路径:";
	std::cin>>filename;

	//打开文件
	fopen_s(&pf,filename,"wb");
	//写入
	fwrite(filedata,1,filesize,pf);
	//关闭文件
	fclose(pf);
	//释放内存
	free(filedata);
	std::cout<<"备份成功";
	system("pause");
}