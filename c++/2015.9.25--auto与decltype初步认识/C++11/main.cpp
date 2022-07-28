#include <iostream>
#include <vector>
#include <map>
#include <string>
using namespace std;

int x = 1;
int y = 1;
auto add(int a, int b)->decltype(x * y)
{
	return a + b;
}

void main()
{
	//auto自动类型推断
	//auto关键字用来从后面表达式自动由编译器推断前面变量的类型

	//auto a；//错误，auto是通过初始化表达式进行类型推导，如果没有初始化
			  //表达式，就无法确定a的类型
	int b = 1;
	auto c = b;
	vector<int> v;
	auto it = v.begin();
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);

	//序列for循环
	//序列for循环语句允许重复遍历一组序列，而这组序列可以是任何可以重复遍历的序列，
	//如由begin()和end()函数定义的STL序列。所有的标准容器都可用作	
	//这种序列，同时它也同样可以是std::string，初始化列表（list），数组，以及任何由begin()和end()函数定义的序列
	for (auto i : v)
		cout << i << endl;

	map<string, int> m;
	
	m.insert(std::pair<string, int>("a", 1));
	m.insert(std::pair<string, int>("b", 2));
	m.insert(std::pair<string, int>("c", 3));

	for (auto i : m)
		cout << i.first << endl;

	int a[5] = {1,2,3,4,5};
	for (auto i : a)
		cout << i << endl;


	//相反地，decltype是通过表达式来获得类型
	int a = 1;
	declytpe(a) b = 1;	//b就是int类型了
	
	//还有一种就是函数返回类型
	//例如上面的add函数
	cout << add(10, 20) <<endl;

	system("pause");
}