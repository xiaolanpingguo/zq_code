#include <iostream>
#include <windows.h>
#include <vector>
#include <string>

//回调的本质实现就是函数指针，这种回调函数往往不是我们
//自己去调用，而是填写这些函数地址，让其它程序去调用，
//比如消息处理函数是典型的回调使用方式，因为我们提供WinProc
//给WNDCLASS，而一旦出现消息那么系统会去调用WinProc来处理

//再比如二叉树遍历，“遍历”的时候做什么是我们无法预知
//的，那么可以通过填写函数指针来帮助我们实行遍历
struct NODE
{
	int data;
	NODE* left;
	NODE* right;
};
void pre_travel(NODE* p, void (* do_something)(int* data))
{
	if (p)
	{
		(*do_something)(&p->data);
		pre_travel(p->left, do_something);
		pre_travel(p->right, do_something);
	}
} //pre_travel就在回调do_something

void print_node(int* data)
{
	std::cout<<*data<<" ";
}
void add_node(int* data)
{
	*data += 1;
}

void pre_travel2(NODE* p, void (* do_something)(int* data, void* parm), void* parm)
{
	if (p)
	{
		(*do_something)(&p->data, parm);
		pre_travel2(p->left, do_something, parm);
		pre_travel2(p->right, do_something, parm);
	}
}
void add_node(int* data, void* p)
{
	*data += *((int*)p);
}

BOOL __stdcall f(HWND h, LPARAM p)
{
	if (h)
	{
		char buf[256] = {};
		GetWindowTextA(h, buf, 256);
		//std::cout<<buf<<std::endl;
		std::vector<std::string>* q = (std::vector<std::string>*)p;
		q->push_back(std::string(buf));
	}

	return true;
}

void main()
{
	NODE n1 = {1};
	NODE n2 = {2};
	NODE n3 = {3};
	NODE n4 = {4};
	NODE n5 = {5};
	NODE n6 = {6};
	n1.left = &n2;
	n1.right = &n3;
	n2.left = &n4;
	n4.left = &n5;
	n4.right = &n6;

	//pre_travel(&n1, print_node); std::cout<<std::endl;
	//pre_travel(&n1, add_node);
	//pre_travel(&n1, print_node); std::cout<<std::endl;

	int x = 5;
	pre_travel2(&n1, add_node, &x);

	pre_travel(&n1, print_node); std::cout<<std::endl;

	//EnumWindows(void (* cl)(HWND hwnd))
	//for (遍历所有的窗口句柄)
	//  (* cl)(hwnd);

	std::vector<std::string> v;
	EnumWindows(f, (LPARAM)&v);
	
	system("pause");
}