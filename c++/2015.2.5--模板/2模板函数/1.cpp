#include <iostream>

//template表示下面的函数是一个模板函数
//，然后<>中用关键字typename定义了一个模
//板参数T，这个T代表一个类型，在具体的
//函数返回值，形式参数表，函数体中就可以
//用这个T类型了，模板函数不是宏

template <typename T>
T Add(T a,T b)
{
	T c = a + b;
	return c;
}

//普通的函数不管是否调用都会被编译并检查错误
//模板函数如果不调用就不会被编译,也不会检查错误.
//(用实际的类型替换模板参数后的调用)

struct _ABC
{
	char a;
	short b;
	int c;
	_ABC operator + (const _ABC& that)
	{
		_ABC abc = {a + that.a, b + that.b,c + that.c};
		return abc;
	}
};

template <typename T1,typename T2>
void PrintTT(T1 t1,T2 t2)
{
	std::cout<<t1<<" "<<t2<<std::endl;
}

//template <typename T>
//void sortPX(T* p ....)
//{}
void main()
{
	int x = Add<int>(1,2);
	float y = Add<float>(1.0f,3.5f);

	_ABC t1 = {1,2,3};
	_ABC t2 = {4,5,6};

	_ABC t3 = Add<_ABC>(t1,t2);

	PrintTT<char,int>('a',15);
	//在使用模板函数的时候，函数名和形式
	//参数表前加上<>，里面写上我们具体的
	//类型，一旦有了这种调用，那么编译器
	//将真正的生成那个类型的版本的函数。
	//模板函数支持任何类型，只是使用时要
	//注意该类型是否支持某些运算.
	system("pause");
}

