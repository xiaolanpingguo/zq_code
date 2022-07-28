//---------------------------
//该文件为文件读取类，主要负责读取
//地图文件存档文件
//---------------------------

#ifndef _READFILE_H_
#define _READFILE_H_

class CMap;

class CReadFile
{
public:
	//读取总地图，该函数在打开可执行文件的时候就应该调用
	void ReadSMap(const char* fileName,CMap* map);

	//读取存档
	void ReadSave(const char* fileName,CMap* map);
};

#endif