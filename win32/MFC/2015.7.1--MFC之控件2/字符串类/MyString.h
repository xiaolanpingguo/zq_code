#ifndef _MY_STRING_H_
#define _MY_STRING_H_

#include <iostream>
#include <cassert>

class CMyString
{
	int len; //没有算结束符
	char* str;

public:

	//无参构造
	CMyString()
	{
		len = 0;
		str = new char[len + 1];
		str[0] = 0;
	}

	//带参构造
	CMyString(const char* s)
	{
		len = (int)strlen(s);
		str = new char[len + 1];
		strcpy_s(str, len + 1, s);
	}

	//拷贝构造
	CMyString(const CMyString& that)
	{
		len = that.len;
		str = new char[len + 1];
		strcpy_s(str, len + 1, that.str);
	}

	//析构
	~CMyString()
	{
		delete [] str;
	}

	//同类赋值
	CMyString& operator = (const CMyString& that)
	{
		if (this != &that)
		{
			delete [] str;
			len = that.len;
			str = new char[len + 1];
			strcpy_s(str, len + 1, that.str);
		}
		return *this;
	}

	//赋值
	CMyString& operator = (const char* s)
	{
		delete [] str;
		len = (int)strlen(s);
		str = new char[len + 1];
		strcpy_s(str, len + 1, s);
		return *this;
	}

	//同类加法
	CMyString operator + (const CMyString& that)
	{
		CMyString ms; //调用了无参构造
		delete [] ms.str; //首先释放在无参构造中开辟的堆内存
		ms.len = len + that.len;
		ms.str = new char[ms.len + 1];
		strcpy_s(ms.str, ms.len + 1, str);
		strcat_s(ms.str, ms.len + 1, that.str);
		return ms;
	}

	//加法
	CMyString operator + (const char* s)
	{
		CMyString ms; //调用了无参构造
		delete [] ms.str; //首先释放在无参构造中开辟的堆内存
		ms.len = len + (int)strlen(s);
		ms.str = new char[ms.len + 1];
		strcpy_s(ms.str, ms.len + 1, str);
		strcat_s(ms.str, ms.len + 1, s);
		return ms;
	}

	//同类自赋值加法
	CMyString& operator += (const CMyString& that)
	{
		int cur_len = len + that.len;
		char* cur_str = new char[cur_len + 1];
		strcpy_s(cur_str, cur_len + 1, str);
		strcat_s(cur_str, cur_len + 1, that.str);
		delete [] str;
		len = cur_len;
		str = cur_str;
		return *this;
	}

	//同类自赋值加法
	CMyString& operator += (const char* s)
	{
		int cur_len = len + (int)strlen(s);
		char* cur_str = new char[cur_len + 1];
		strcpy_s(cur_str, cur_len + 1, str);
		strcat_s(cur_str, cur_len + 1, s);
		delete [] str;
		len = cur_len;
		str = cur_str;
		return *this;
	}

	//char自赋值加法
	CMyString& operator += (char c)
	{
		int cur_len = len + 1;
		char* cur_str = new char[cur_len + 1];
		strcpy_s(cur_str, cur_len + 1, str);
		cur_str[cur_len - 1] = c;
		cur_str[cur_len] = 0;
		delete [] str;
		len = cur_len;
		str = cur_str;
		return *this;
	}

	char& operator [] (int index)
	{
		assert(index >= 0 && index < len);
		return str[index];
	}

	const char* GetString()
	{
		return str;
	}

	int GetLength()
	{
		return len;
	}
};

#endif