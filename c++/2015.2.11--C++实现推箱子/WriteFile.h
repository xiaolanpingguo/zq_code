#ifndef _WRITEFILE_H_
#define _WRITEFILE_H_

class CMap;

//文件写入。主要用于存档
class CWriteFile
{
public:
	//保存文件
	void SaveFile(const char* filename,CMap* map);
};

#endif