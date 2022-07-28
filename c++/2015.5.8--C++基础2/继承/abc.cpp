#include <iostream>
#include <assert.h>

//继承就是子类自动拥有父类的所有成员

//class A
//{
//public:
//	int a1;
//	void a2()
//	{}
//};
//class B : public A
//{
//public:
//	int b1;
//	void b2()
//	{}
//};
//上面的代码将使得编译器这么来处理B类
//class B
//{
//public:
//	int a1;
//	void a2()
//	{}
//	int b1;
//	void b2()
//	{}
//};

int x;
class A
{
public:
	int x;
};
class B : public A
{
public:
	int x;
	void f(int x)
	{
		x = 1; //形式参数x
		this->x = 1; //B的成员变量x
		A::x = 1; //A的成员变量x（B继承自A得到的A的部分）
		::x = 1; //全局变量x（作用域运算符之前不加类名或者名字空间，则表示全局域）
	}
};

class C
{
public:
	C(){std::cout<<"C构造"<<std::endl;}
	~C(){std::cout<<"C析构"<<std::endl;}
};
class D : public C
{
public:
	D(){std::cout<<"D构造"<<std::endl;}
	~D(){std::cout<<"D析构"<<std::endl;}
};
class E : public D
{
public:
	E(){std::cout<<"E构造"<<std::endl;}
	~E(){std::cout<<"E析构"<<std::endl;}
};
void f()
{
	E e;
}

class F
{
private:
	int f1;
protected:
	int f2;
public:
	int f3;
	void x()
	{
		f1 = 1;
		f2 = 1;
		f3 = 1;
	}
};
class G : public F
{
	void y()
	{
		//f1 = 1; //f1是不允许访问，因为f1是其父类的私有成员
		f2 = 1;
		f3 = 1;
	}
};

class H
{};
class I : public H
{};

void main()
{
	//1）子类和父类的成员之间的命名冲突
	B b;
	std::cout<<sizeof(b)<<std::endl;
	b.x = 1; //B的成员变量x
	b.A::x = 1; //A的成员变量x（B继承自A得到的A的部分）

	//2）子类和父类的构造、析构
	f();
	//在继承体系下面的类对象生存周期
	//a）开辟内存
	//b）最顶层父类构造、次顶层父类构造...当前类构造
	//c）使用类对象
	//d）当前类析构...次顶层父类析构、最顶层父类析构
	//e）释放内存

	//3）保护访问权限
	//访问权限			public成员		protected成员		private成员
	//类中成员函数		√				√					√
	//子类成员函数		√				√					×
	//外部函数			√				×					×
	std::cout<<sizeof(G)<<std::endl;
	G g;
	//g.f1 = 1; //main函数相对于F类来说是外部函数，除了F类的共有部分其它都不能访问
	//g.f2 = 1;
	g.f3 = 1;
	//不在继承体系下的类：成员变量私有、成员函数公有
	//要派生子类的类：成员变量保护、成员函数公有

	//4）继承的种类
	//继承种类				子类public继承		子类protected继承		子类private继承
	//父类公有成员变为		子类公有成员		子类保护成员			子类私有成员
	//父类保护成员变为		子类保护成员		子类保护成员			子类私有成员
	//父类私有成员变为		不能访问成员		不能访问成员			不能访问成员
	//绝大部分情况都是public继承

	//5）子类父类之间的赋值
	H h;
	I i;
	h = i; //父类对象 = 子类对象 √
	//i = h; //子类对象 = 父类对象 ×
	H* p1 = &i; //父类指针 = 子类对象地址 √
	//I* p2 = &h; //子类指针 = 父类对象地址 ×
	H& r1 = i; //父类引用 = 子类对象 √
	//I& r2 = h; //子类引用 = 父类对象 ×
	//=左侧只能是父类（对象、指针、引用）
	//=右侧只能是子类（对象、地址、对象）
		
	system("pause");
}