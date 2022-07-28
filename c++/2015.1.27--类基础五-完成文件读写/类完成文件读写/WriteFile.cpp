#include "WriteFile.h"
#include <iostream>

//CWriteFile::CWriteFile()
//:
//m_Size(4),m_Length(0),m_Data(new char[m_Size])
//{
//	
//}

void CWriteFile::Open(const char* filename)
{
	//m_FileName
	strcpy_s(m_FileName,256,filename);

	m_Size = 4;

	m_Length = 0;

	m_Data = new char[m_Size];
}
void CWriteFile::Close()
{
	FILE* pf = 0;

	fopen_s(&pf,m_FileName,"wb");
	if(!pf)
		return;
	fwrite(m_Data,1,m_Length,pf);
	fclose(pf);
	delete []m_Data;
}
void CWriteFile::WriteBool(bool data)
{
	_addmem(sizeof(data));
	*((bool*)(m_Data + m_Length)) = data;
	m_Length += sizeof(data);
}

void CWriteFile::WriteShort(short data)
{
	_addmem(sizeof(data));
	*((short*)(m_Data + m_Length)) = data;
	m_Length += sizeof(data);
}


void CWriteFile::WriteChar(char data)
{
	_addmem(sizeof(data));
	*((char*)(m_Data + m_Length)) = data;
	m_Length += sizeof(data);
}

void CWriteFile::WriteString(const char* data)
{
	int addlen = (int)strlen(data) + 1;
	_addmem(addlen);
	memcpy(m_Data + m_Length,data,addlen);
	m_Length += addlen;
}

void CWriteFile::WriteMemory(const void* data,int count)
{
	_addmem(count);
	memcpy(m_Data + m_Length,data,count);
	m_Length += count;
} 

