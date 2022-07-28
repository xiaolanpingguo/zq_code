
//C++的文件读写

#include <iostream>
#include <fstream>
using namespace std;

//在fstream里，封装了文件读写的相关函数，其中：
//ofstream  ：文件写操作 内存写入存储设备   
//ifstream  ：文件读操作，存储设备读区到内存中  
//fstream   ：读写操作，对打开的文件可进行读写操作 

//而在文件打开的函数open函数有以下几个选项，open(filename, opt);
//ios::in	 :	为输入(读)而打开文件
//ios::out	 :	为输出(写)而打开文件
//ios::ate	 :	初始位置：文件尾
//ios::app	 :	所有输出附加在文件末尾
//ios::trunc :	如果文件已存在则先删除该文件
//ios::binary:	二进制方式
//
int main()
{
	//打开文件
	ofstream out;
	out.open("1.txt", ios::in|ios::out|ios::binary);
	if (!out.is_open())
	{
		cout << "out打开文件失败：1.txt" << endl;
		out.close();
		system("pause");
		return -1;
	}

	//开始写文件
	out << "abc\n";
	out << "123\n";
	out.close();

	//也可以用构造初始化的方式打开文件，因为构造函数里面
	//会调用open函数
	ifstream in("1.txt", ios::in|ios::binary);
	if (!in.is_open())
	{
		cout << "in打开文件失败：1.txt" << endl;
		in.close();
		system("pause");
		return -1;
	}

	char buf[256] = {};
	//循环读取，eof代表到达文件末尾就会返回true
	//除了eof()以外，还有一些验证流的状态的成员函数（所有都返回bool型返回值）：
	//bad():如果在读写过程中出错，返回true。例如：当我们要对一个不是打开为写状态的文件进行写入时，
	//		或者我们要写入的设备没有剩余空间的时候
	//fail():除了与bad() 同样的情况下会返回 true 以外，加上格式错误时也返回true，
	//		例如当想要读入一个整数，而获得了一个字母的时候
	//eof():如果读文件到达文件末尾，返回true
	//good():这是最通用的：如果调用以上任何一个函数返回true的话，此函数返回false 
	//while (!in.eof())
	//{
	//in.getline(buf, 256);
	//cout << buf << endl;
	//}
	
	//seekg(offset, dir),
	//offset是一个位移值，为Long型，=0是当前，>0向后移，<0则向前移。
	//dir有3个参数，ios::beg文件开头，ios::end文件结尾，ios::cur当前指针位置.
	//比如seekg（10L，beg），表示文件开头向后移10个字节，在用cout<<tellg()显示位移后的位置

	//tellg返回当前流指针的位置
	in.seekg(0, ios::end);
	auto filesize =  in.tellg();
	cout << "filesize1:" << filesize << endl;
	in.seekg(100, ios::beg);
	auto end = in.tellg();
	cout << "end:" << end << endl;

	in.close();


	//读写二进制文件
	out.open("111", ios::in|ios::out|ios::binary);
	out.write("123abc789", 10);
	out.close();

	in.open("111", ios::in|ios::out|ios::binary);
	in.seekg(0, ios::end);
	auto fs = in.tellg();
	cout << "filesize2:" << fs << endl;

	//读取的话记得移动读写指针到开头
	in.seekg(0, ios::beg);
	char buf1[32] = {};
	in.read(buf1, 32);
	cout << buf1 << endl;


	//关闭文件以使文件重新变为可访问
	out.close();
	in.close();
#ifdef WIN32
	system("pause");
#endif
	return 0;
}