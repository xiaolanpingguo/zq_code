#include <windows.h>
#include <iostream>

void main()
{
	//读取字符串
	char buf[256];
	GetPrivateProfileStringA(
		"Baseline",
		"Dir",
		"失败！", //读取失败的字符串
		buf,
		256,
		".\\setup.ini");
	std::cout<<buf<<std::endl;

	GetPrivateProfileStringA(
		"Baseline",
		"Dir2",
		"失败！", //读取失败的字符串
		buf,
		256,
		".\\setup.ini");
	std::cout<<buf<<std::endl;

	GetPrivateProfileStringA(
		"Baseline",
		"FileName",
		"失败！", //读取失败的字符串
		buf,
		256,
		".\\setup.ini");
	std::cout<<buf<<std::endl;

	//读取内存
	char x[32] = {};
	GetPrivateProfileStructA(
		"qwe",
		"a1",
		x,
		6, //只能填写ini中字节的数量，不包括最后的校检字节
		".\\xyz.ini");
	
	int y;
	GetPrivateProfileStructA(
		"qwe",
		"a2",
		&y,
		4, //只能填写ini中字节的数量，不包括最后的校检字节
		".\\xyz.ini");

	GetPrivateProfileStringA(
		"qwe",
		"a2",
		"失败！", //读取失败的字符串
		buf,
		256,
		".\\xyz.ini");
	std::cout<<buf<<std::endl;

	system("pause");
}