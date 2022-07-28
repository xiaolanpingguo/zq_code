#include "Tree.h"
#include <iostream>
#include <string>

void main()
{
	char fn[256];
	std::cout<<"请输入要读取的文件：";
	std::cin>>fn;

	//读取文件
	FILE* pf = 0;
	fopen_s(&pf, fn, "rb");
	if (!pf)
	{
		std::cout<<"无法打开指定文件，";
		system("pause");
		return;
	}
	fseek(pf, 0, SEEK_END);
	int fs = ftell(pf);
	rewind(pf);
	char* fd = (char*)malloc(fs + 1);
	fread(fd, 1, fs, pf);
	fclose(pf);
	fd[fs] = 0;

	//过滤文件
	std::string str;
	for (int i = 0; i < fs; ++i)
	{
		if (fd[i] > ' ')
			str += fd[i];
	}
	free(fd);

	//树的组织

	//创建根节点
	TN* root = createTN(); root->data = fn;

	//设置当前父节点
	TN* parent = root;

	//"123{abc{}def{xyz{}kkk{1{}2{}3{}}456{}}}"
	//data=123

	std::string data;
	for (int i = 0; i < (int)str.length(); ++i)
	{
		if (str[i] == '{')
		{
			TN* p = createTN();
			p->data = data;
			data.clear();
			insertTN(parent, p);
			parent = p;
		}
		else if (str[i] == '}')
		{
			parent = parent->parent;
		}
		else
			data += str[i];
	}

	preTN(root, 0);

	system("pause");
}