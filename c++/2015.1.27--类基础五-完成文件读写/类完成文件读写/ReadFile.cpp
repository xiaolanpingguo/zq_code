#include "ReadFile.h"
#include <iostream>

bool CReadFile::Open(const char* filename)
{
	FILE* fp = 0;
	fopen_s(&pf,filename,"rb");
	if(!pf)
		return false;
	fseek(pf,0,SEEK_END);
	m_Size = ftell(pf);
	rewind(pf);
	m_Data = new char[m_Size];
	fread(m_Data,1,m_Size,pf);
	fclose(pf);
	m_Pos = 0;
	return true;
}
void CReadFile::Close()
{
	if(m_Data)
		delete []m_Data;
}
bool CReadFile::Read_Char(char* data)
{
	if(m_Size - m_Pos < sizeof(*data))
		return false;
	*data = *((char*)(m_Data + m_Pos));
	
	m_Pos += sizeof(*data);
	return true;
}
bool CReadFile::Read_Short(short* data)
{
	if(m_Size - m_Pos < sizeof(*data))
		return false;
	*data = *((short*)(m_Data + m_Pos));
	
	m_Pos += sizeof(*data);
	return true;
}
bool CReadFile::Read_String(char* data)
{
	int len = (int)strlen(m_Data + m_Pos);
	if(len > m_Size - m_Pos - 1)
		return false;
	memcpy(data,m_Data + m_Pos,len + 1);
	m_Pos += len + 1;
	return true;
}
bool CReadFile::Read_Memory(void* data,int count)
{
	if(m_Size - m_Pos < count)
		return false;
	memcpy(data,m_Data + m_Pos,count);
	m_Pos += count;
	return true;
}