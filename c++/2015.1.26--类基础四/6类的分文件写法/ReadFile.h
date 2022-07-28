#ifndef _READFILE_H_
#define _READFILE_H_

class CReadFile
{
private:
	int m_Size;//文件大小
	int m_Pos;//当前读取位置
	char* m_Data;//数据
public:
	CReadFile();
	~CReadFile();
	bool Open(const char* filename);
	//....
};

#endif