#include <iostream>
#include "ReadFile.h"

CReadFile::CReadFile()
:
m_Data(0)
{
	//m_Data = new char[m_Size];
}
CReadFile::~CReadFile()
{
	if(m_Data)
		delete []m_Data;
}
bool CReadFile::Open(const char* filename)
{
	FILE* pf = 0;
	fopen_s(&pf,filename,"rb");
	if(!pf)
		return false;
	if(m_Data)
		delete []m_Data;
	fseek(pf,0,SEEK_END);
	m_Size = ftell(pf);
	rewind(pf);
	m_Data = new char[m_Size];
	fread(m_Data,1,m_Size,pf);
	fclose(pf);
	m_Pos = 0;
	return true;
}