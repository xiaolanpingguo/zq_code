#include <iostream>
#include <vector>
using namespace std;

//参考资料：http://www.ibm.com/developerworks/cn/aix/library/1307_lisl_c11/
//	    http://www.cnblogs.com/hujian/archive/2012/02/13/2348621.html

void f1(int &r)
{
	cout << "左值引用：" << r << endl;
}

void f1(int &&r)
{
	cout << "右值引用：" << r << endl;
}

void f2(int &&r)
{
	f1(r);
}

class MyString 
{ 
private: 
	char* _data; 
	size_t   _len; 

//拷贝
void _init_data(const char *s) 
{ 
	_data = new char[_len+1]; 
	memcpy(_data, s, _len); 
	_data[_len] = '\0'; 
} 

public: 

//无参构造
MyString() 
{ 
	_data = NULL; 
	_len = 0; 
} 

//带参构造
MyString(const char* p)
{ 
	_len = strlen (p); 
	_init_data(p); 
} 

//拷贝构造
MyString(const MyString& str) 
{ 
	_len = str._len; 
	_init_data(str._data); 
	std::cout << "调用了拷贝构造: " << str._data << std::endl; 
} 

//同类赋值
MyString& operator=(const MyString& str) 
{ 
	if (this != &str) 
	{ 
		_len = str._len; 
		_init_data(str._data); 
	} 
	std::cout << "调用了同类赋值: " << str._data << std::endl; 
	return *this; 
} 

//转移构造
//和拷贝构造函数类似，有几点需要注意：
//参数（右值）的符号必须是右值引用符号，即“&&”。
//参数（右值）不可以是常量，因为我们需要修改右值。
//参数（右值）的资源链接和标记必须修改。否则，右值的析构函数就会释放资源。转移到新对象的资源也就无效了
MyString(MyString &&str)
{
	 std::cout << "调用了转移构造: " << str._data << std::endl; 
    _len = str._len; 
    _data = str._data; 
    str._len = 0; 
    str._data = NULL;
}

//转移赋值操作符
MyString& operator=(MyString&& str) 
{ 
    std::cout << "调用了转移拷贝构造: " << str._data << std::endl; 
    if (this != &str) 
	{ 
      _len = str._len; 
      _data = str._data; 
      str._len = 0; 
      str._data = NULL; 
    } 
    return *this; 
 }

//析构
virtual ~MyString() 
{ 
	if (_data) 
		free(_data); 
} 

}; 

template <typename T>
void myswap1(T& a, T& b)
{
	//这里将进行三次不必要的拷贝操作
	T t = a;
	a = b;
	b = t;
}
template <typename T>
void myswap2(T& a, T& b)
{
	//避免了3次不必要的拷贝操作
	T t = std::move(a);
	a = std::move(b);
	b = std::move(t);
}


void main()
{
	//在C++98中，引用一般是拿来初始化一个左值的
	int a = 1;
	int &b = a;//可以

	//如果要用一个右值来初始化一个引用时，就必须是常引用才行，例如
	//int &c = 1;//不可以，无法从int转换为int&
	const int &c = 1;//可以

	//那在C++11中为了区分左值和右值，分别用&和&&符号来代表对左值和右值的引用
	//注意：做右值引用的时候，右值不可以是常量，因为它要改变
	int d = 1;
	f1(d);	//调用的f1的左值引用
	f1(1);	//调用的f1的右值引用

	//调用的f1的左值引用，那从这就可以看出，之前只有一个2，本来是一个临时量，
	//也就是一个右值，在对它进行右值引用过后，就变成了左值
	f2(2);  

	//那为什么要这么做呢？右值引用是用来支持转移语义的。
	//转移语义可以将资源 ( 堆，系统对象等 ) 从一个对象转移到另一个对象，
	//这样能够减少不必要的临时对象的创建、拷贝以及销毁，
	//能够大幅度提高 C++ 应用程序的性能，临时对象的维护( 创建和销毁 )对性能有严重影响。
	//通过转移语义，临时对象中的资源能够转移其它的对象里。
	//在现有的 C++ 机制中，我们可以定义拷贝构造函数和赋值函数。要实现转移语义，
	//需要定义转移构造函数，还可以定义转移赋值操作符。对于右值的拷贝	
	//和赋值会调用转移构造函数和转移赋值操作符。如果转移构造函数和转移拷贝操作符没有定义，
	//那么就遵循现有的机制，拷贝构造函数和赋值操作符会被调用。
	//普通的函数和操作符也可以利用右值引用操作符实现转移语义

	//在这里，MyString(“Hello”) 和 MyString(“World”) 都是临时对象，也就是右值。
	//虽然它们是临时的，但程序仍然调用了拷贝构造和拷贝赋值，造成了没有意义的资源申请和释放的操作。
	//如果能够直接使用临时对象已经申请的资源，既能节省资源，有能节省资源申请和释放的时间。
	//这正是定义转移语义的目的
	MyString s; 
	s = MyString("Hello");	//调用了转移构造函数
	std::vector<MyString> vec; 
	vec.push_back(MyString("World")); //调用了转移赋值操作函数


	//既然编译器只对右值引用才能调用转移构造函数和转移赋值函数，
	//而所有命名对象都只能是左值引用，如果已知一个命名对象不再
	//被使用而想对它调用转移构造函数和转移赋值函数，
	//也就是把一个左值引用当做右值引用来使用，怎么做呢？标准库提供了函数 std::move，
	//这个函数以非常简单的方式将左值引用转换为右值引用。
	int a1 = 1;
	f1(a1);	//调用了f1的左值引用
	f1(std::move(a1));//经过std::move转换过后，就把a1从左值引用变成了右值引用

	//那具体用在哪呢，比如我们一个swap函数，
	int t1 = 10;
	int t2 = 20;

	myswap1<int>(t1, t2);
	cout << t1 <<"  " << t2 << endl;  
	myswap2<int>(t1, t2);
	cout << t1 <<"  " << t2 << endl;  

	system("pause");
}