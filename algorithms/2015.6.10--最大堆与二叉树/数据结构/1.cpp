#include <iostream>
#include <windows.h>
#include <time.h>
#include <string> //std::string类
#include <string.h> //C语言库中的字符串相关函数的声明所在头文件，比如strlen、strcmp
#include <cstring> //C++对string.h的包装
#include "SqList.h"
#include "LinkList.h"
#include "SqStack.h"
#include "SqQueue.h"
#include "SqSet.h"
#include "SqMap.h"
#include "Hash.h"
#include "MaxHeap.h"
#include "BinaryTree.h"

//线性
//{
	//顺序表（vector）√
	//链式表（list）√
	//顺序队列√、顺序循环队列
	//顺序栈√
	//顺序集合√
	//顺序映射√
	//顺序哈希表√
//}

//树型
//{
	//顺序最大堆
	//链式树
	//链式二叉树
	//搜索树
	//AVL树
	//红黑树（set、map）
//}

//其它
//{
//	内存池
//}

//算法
//排序：冒泡√、选择√、最大堆、快速、归并
//查找：折半√、KMP
//寻路：广度、深度、A星

class ZuoBiao
{
	int x, y;
public:
	ZuoBiao& operator ++()
	{
		++x;
		++y;
		return *this;
	}
	ZuoBiao operator ++(int)
	{
		ZuoBiao zb = *this;
		++x;
		++y;
		return zb;
	}
};

#include <assert.h>

class A
{
public:
	class B
	{};
};
A::B f1()
{
	A::B b;
	return b;
}

//如果一个函数返回一个模板类中的类，那么这个返回值前面必须带上typename

template <typename T>
class C
{
public:
	class D
	{};
};
template <typename T>
typename C<T>::D f2()
{
	C::D d;
	return d;
}

#include <stack>
#include <queue>

int add(char a, float b)
{
	return (int)a + (int)b;
}
int sub(char a, float b)
{
	return (int)a - (int)b;
}

int hash_func(char* key)
{
	return (key[0] + key[strlen(key) - 1]) % 256;
}

int hash_func2(std::string key)
{
	return (key[0] + key[key.length() - 1]) % 256;
}

#define _MAX_NUM 100000
int a[_MAX_NUM];
int b[_MAX_NUM];

void select_sort(int* p, int n)
{
	int num = n - 1;
	for (int i = 0; i < num; ++i)
	{
		int j = i;
		for (int k = j + 1; k < n; ++k)
		{
			if (p[j] < p[k])
				j = k;
		}
		if (j != i)
		{
			int t = p[i];
			p[i] = p[j];
			p[j] = t;
		}
	}
}

void main()
{
	_BTN<char>* bt1 = createBTN<char>(); bt1->data = 'A';
	_BTN<char>* bt2 = createBTN<char>(); bt2->data = 'B';
	_BTN<char>* bt3 = createBTN<char>(); bt3->data = 'C';
	_BTN<char>* bt4 = createBTN<char>(); bt4->data = 'D';
	_BTN<char>* bt5 = createBTN<char>(); bt5->data = 'E';
	_BTN<char>* bt6 = createBTN<char>(); bt6->data = 'F';
	_BTN<char>* bt7 = createBTN<char>(); bt7->data = 'G';

	insertBTN(bt1, bt2);
	insertBTN(bt1, bt3, false);
	insertBTN(bt2, bt4);
	insertBTN(bt2, bt5, false);
	insertBTN(bt4, bt6);
	insertBTN(bt6, bt7, false);

	//pre_printBTN(bt1); std::cout<<std::endl;
	//mid_printBTN(bt1); std::cout<<std::endl;
	//post_printBTN(bt1); std::cout<<std::endl;

	std::cout<<heightBTN(bt1)<<std::endl;
	std::cout<<heightBTN(bt2)<<std::endl;
	std::cout<<heightBTN(bt3)<<std::endl;

	eraseBTN(bt2);

	//srand((unsigned int)time(0));
	//for (int i = 0; i < _MAX_NUM; ++i)
	//	a[i] = b[i] = rand();

	//int t1 = GetTickCount(); //得到开机到目前为止的毫秒数
	//select_sort(a, _MAX_NUM);
	//std::cout<<GetTickCount() - t1<<std::endl;

	//CMaxHeap<int> mh;
	//int t2 = GetTickCount(); //得到开机到目前为止的毫秒数
	//for (int i = 0; i < _MAX_NUM; ++i)
	//	mh.Push(b[i]);
	//while (mh.Size() > 0)
	//{
	//	int t;
	//	mh.Front(&t);
	//	mh.Pop();
	//	//凡是内存和其它设备进行数据交互的操作都慢，比如
	//	//打印、读写文件
	//	//std::cout<<t<<std::endl;
	//}
	//std::cout<<GetTickCount() - t2<<std::endl;

	//最大堆排序不算内排序中最快，所谓内排序就是
	//内存中的数据排序，还有外排序主要就是指的在
	//外存中的排序

	////s.

	////assert里面可以填写任何一个有结果的表达式，若
	////这个表达式的结果为真，则什么都不做，若干这个
	////表达式的结果为假，则系统直接强制使用exit退出
	////程序并给出详细的出错信息，assert称之为断言，
	////常常用在调试
	////assert(0);

	////int a = 0;
	////++a = 1; //前置自增表达式的结果可以放在=左侧，也就是说前置自增表达式的结果就是一个变量
	////a++ = 1; //后置自增表达式的结果不能放在=左侧，也就是说后置自增表达式的结果不是一个变量而是一个临时量

	//CLinkList<int> sqlist1;
	//sqlist1.Push_Back(1);
	//sqlist1.Push_Back(2);
	//sqlist1.Push_Back(3);
	//sqlist1.Push_Back(4);

	////顺序表是允许用整数相当于下标进行遍历操作的
	////for (int i = 0; i < sqlist1.Size(); ++i)
	////{
	////	int* p = sqlist1.At(i);
	////	std::cout<<*p<<std::endl;
	////}

	//CLinkList<int>::Iterator it;

	//for (it = sqlist1.Begin(); it != sqlist1.End(); )
	//{
	//	if (*it == 3)
	//		it = sqlist1.Erase(it);
	//	else
	//		++it;
	//}
	//
	//for (it = sqlist1.Begin(); it != sqlist1.End(); ++it)
	//{
	//	std::cout<<*it<<std::endl;
	//}

	//CSqQueue<int> s;
	//s.Push(1);
	//s.Push(2);
	//s.Push(3);
	//s.Push(4);
	//while (!s.Empty())
	//{
	//	int data;
	//	s.Front(&data);
	//	s.Pop();
	//	std::cout<<data<<std::endl;
	//}

	//CMap<int, char> map;
	//map.Insert(0, 'A');
	//map.Insert(3, 'B');
	//map.Insert(2, 'D');
	//map.Insert(1, 'E');
	//map.Insert(-2, 'C');
	//for (int i = 0; i < map.Size(); ++i)
	//{
	//	std::cout<<map.At(i)->data<<std::endl;
	//}

	////指向数据的指针
	////int* p = add;

	////指向函数的指针，p要求函数的返回值
	////必须是int，且形式参数表必须是(char,float)
	//int (*p)(char, float) = add;

	//std::cout<<(*p)(1,2)<<std::endl;

	//p = sub;

	//std::cout<<(*p)(1,2)<<std::endl;

	////通过小于运算符判断两个数据是否相等
	////int x, y;
	////std::cin>>x>>y;
	////if (!(x < y) && !(y < x))
	////	std::cout<<"相等"<<std::endl;

	//CHash<char*, char> hash(hash_func);

	////函数查找是没有问题的，但是内部的<运算符
	////并不是按照字符串的比较法则，而是按照地址
	////的大小进行比较的
	////hash.Insert("abc", 'x');
	////hash.Insert("def", 'y');
	////hash.Insert("cba", 'z');
	////hash.Insert("fed", 'w');
	////std::cout<<hash.Find("abc")->data<<std::endl;
	////std::cout<<hash.Find("def")->data<<std::endl;
	////std::cout<<hash.Find("cba")->data<<std::endl;
	////std::cout<<hash.Find("fed")->data<<std::endl;

	////下面的代码是比较的两个字符串字面常量的地址大小
	//if ("abc" > "def")
	//{
	//	std::cout<<"abc > def"<<std::endl;
	//}
	////下面的代码是比较的两个字符串字面常量的内容大小
	//if (strcmp("abc", "def") == 1)
	//{
	//	std::cout<<"abc > def"<<std::endl;
	//}

	////C语言编译器扫描到字符串字面常量，如果出现了多次
	////相同的字符串字面常量，那么其地址都是一样的
	//char* p1 = "123abc";
	//char* q1 = "123abc"; //左侧p1和q1将得到相同的地址
	//char* r1 = "123" "abc"; //编译器会自动连接这种写法的字符串字面常量

	////如果要真正用字符串的内容比较法则来进行插入处理，建议
	////使用std::string作为KEY值
	//CHash<std::string, char> hash2(hash_func2);

	////std::string是重写了[]运算符的
	//std::string x = "abc";
	//std::cout<<x[0]<<std::endl;
	//std::cout<<x[1]<<std::endl;
	//std::cout<<x[2]<<std::endl;

	


	system("pause");
}