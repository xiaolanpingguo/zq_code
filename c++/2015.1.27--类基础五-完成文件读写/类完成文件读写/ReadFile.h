#ifndef _READFILE_H_
#define _READFILE_H_

class CReadFile
{
	 int m_Size;//文件大小
	 int m_Pos;//读取位置
	 char* m_Data;//数据
public:
	bool Open(const char* filename);
	void Close();
	bool Read_Char(char* data);
	bool Read_Short(short* data);
	bool Read_String(char* data);
	bool Read_Memory(void* data,int count);
};

#endif