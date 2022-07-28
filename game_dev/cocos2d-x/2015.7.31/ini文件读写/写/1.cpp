#include <windows.h>
#include <iostream>

//微软为了方便程序读写简单数据，所以推出一套操作ini文件
//的函数，利用这套函数可以很容易地读写ini文件中的内容，
//注意ini文件的格式如下：
//FileName.ini
//[AppName1]
//KeyName1=String1
//KeyName2=String2
//...
//KeyName3=String3
//
//[AppName2]
//KeyName1=String1
//KeyName2=String2
//...
//KeyName3=String3

void main()
{
	//写入字符串
	WritePrivateProfileStringA(
		"ABC", //块名
		"a", //键
		"123", //值
		".\\xyz.ini");
	WritePrivateProfileStringA(
		"ABC", //块名
		"b", //键
		"456", //值
		".\\xyz.ini");
	WritePrivateProfileStringA(
		"你好", //块名
		"c", //键
		"世界", //值
		".\\xyz.ini");
	WritePrivateProfileStringA(
		"你好", //块名
		"c", //键
		"hello", //值
		".\\xyz.ini");
	WritePrivateProfileStringA(
		"你好", //块名
		"c", //键
		"hello", //值
		".\\qwe.ini");

	//写入一段内存，最后写入的时候会多出一个校检字节，这个字节
	//是所有的字节的和
	WritePrivateProfileStructA(
		"OOO",
		"a1",
		"123abc",
		6,
		".\\xyz.ini");
	int x = 0x11223344; //44 33 22 11
	WritePrivateProfileStructA(
		"OOO",
		"a2",
		&x,
		4,
		".\\xyz.ini");

	system("pause");
}