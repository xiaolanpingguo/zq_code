#include <iostream> 
using namespace std;


int main()
{
	//auto推导规则：
	//1.当不声明为指针或引用时，auto的推导结果和初始化表达式抛弃引用
	//和cv(const, volatile)限定符后类型一致
	//2.当声明为指针或引用时,auto的推导结果将保持初始化表达式的cv属性

	auto a = 0;		//a->int, a被推导为int
	auto b = &a;	//b->int*, auto被推导为int*
	auto& c = a;	//c->int&, auto被推导为int

	//d->int, auto被推导为int,表达式是一个引用类型时,auto会把引用类型抛弃
	//直接推导为原始的int类型
	auto d = c;		

	//const auto会在编译时被替换为const int
	const auto e = a;	//e->const int

	//表达式带有const类型时,auto会把const类型抛弃
	//直接推导为原始的int类型
	auto f = e;			//f->int

	//当auto和引用(指针也可以)结合时，auto的推导将保留表达式的const属性
	const auto& g = a;	//g->const int&
	auto& h = g;		//h->const int&

	//auto的受限：
	//1.不能用于函数参数,
	//比如 void f(auto a = 1){}
	//2.不能用于非静态成员变量
	//struct A
	//{
	//	auto a = 1;//这里错误，不能用于非静态成员变量
	//	static const auto x = 2;
	//};
	//3.无法定义数组
	//int arr[10]={0};
	//int c[10] = arr;


	//decltype
	int x = 0;
	decltype(x) y = 1;	//y->int
	decltype(x + y) z = 0;//z->int
	
	const int& i = x;
	decltype(i) j = y;	//j->const int&

	const decltype(z)* p = &z;//*p->const int, p->const int*
	decltype(z)* pi = &z;//*pi->int, pi->int*
	decltype(pi)* pp = &pi;//*pp->int*, pp->int**

	//decltype(exp)推导规则
	//1.exp是标识符，类访问表达式,decltype(exp)和exp的类型一致
	//这个跟前面的上面的推导一样,对于标识符表达式而言,decltype的
	//推导结果就和这个变量的类型定义一致,如果是类里面的一个数据类型
	//也符合这个规则
	//2.exp是函数调用,decltype(exp)和返回值的类型一致
	int& fun_int_r();	//左值
	int&& fun_int_rr();	//x值(右值引用)
	int fun_int();		//纯右值
	const int& fun_cint_r();	//左值
	const int&& fun_cint_rr();	//x值
	const int fun_cint();		//纯右值

	decltype(fun_int_r()) a1 = x;//a1->int&
	decltype(fun_int_rr()) b1 = 0;//a1->int&&
	decltype(fun_int()) c1 = 0;//c1->int
	decltype(fun_cint_r()) a2 = x;//a2->const int&
	decltype(fun_cint_rr()) b2 = 0;//b2->const int&&

	//不是const int，因为函数返回的Int是一个纯右值，对于纯右值而言
	//只有类类型可以携带cv限定符，此外则一般忽略掉cv限定
	decltype(fun_cint()) c2 = 0;//c2->int

	//Foo是一个类
	//const Foo fun_cfoo();
	//decltype(fun_cfoo()) ff = Foo();//ff->const Foo

	//3.其他情况,若exp是一个左值,则decltype(exp)是exp类型的左值引用
	//否则和exp类型一致
	//带括号的表达式和加法运算表达式
	//struct Foo{int x;};
	//const Foo foo = Foo();

	//decltype(foo.x) a = 0;	//a->int

	//foo.x是一个左值,可知括号表达式也是一个左值,按照推导规则3
	//decltype的结果将是一个左值引用
	//decltype((foo.x)) b = a;	//b->const int&

	//
	//int n =0 , m = 0;
	//decltype(n + m) c = 0;	//c->int, 规则3
	//decltype(n += m) d = c;	//d->int&, 规则3



	////auto和decltype的结合使用
	//这种方式一般用在返回值类型依赖与参数而导致难以确定返回值类型的问题
	//int& foo(int& i);
	//float foo(float& f);

	//template <typename T>
	//auto func(T& val) ->decltype(foo(val))
	//{
	//	return foo(val);
	//}

	std::getchar();
	return 0;
}
