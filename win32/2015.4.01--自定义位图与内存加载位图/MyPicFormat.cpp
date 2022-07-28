#include "MyPicFormat.h"
#include <iostream>


bool Create_mpf_file(char** bmp,//原始的位图文件名数组
					 int num,//自定义位图总数
					 const char* mpf)//要生成的自定义位图文件的名称
{
	FILE* pf = 0;
	fopen_s(&pf,mpf,"wb");
	//将总数量写入文件
	fwrite(&num,4,1,pf);

	for(int i = 0; i < num;++i)
	{
		FILE* qf = 0;
		fopen_s(&qf,bmp[i],"rb");
		if(!qf)
		{
			fclose(pf);
			return false;
		}

		fseek(qf,0,SEEK_END);
		int fs = ftell(qf);
		rewind(qf);

		char* p = new char[fs];
		fread(p,1,fs,qf);
		fclose(qf);
		fwrite(p,fs,1,pf);
		delete []p;
	}

	fclose(pf);
	return true;
}