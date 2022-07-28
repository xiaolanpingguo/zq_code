#include <iostream>

//struct ABC
//{
//	ABC x; //结构体中成员变量不能是自己类型
//};
//struct DEF
//{
//	DEF* x; //结构体中成员变量可以是自己类型的指针
//};

struct NODE
{
	int data; //数据
	NODE* next; //指针
};

struct NODE2
{
	int data; //数据
	NODE2* pre; //前指针
	NODE2* next; //后指针
};

void main()
{
	NODE n1 = {1};

	//n1.next = &n1;
	//for (NODE* p = &n1; p; p = p->next)
	//	std::cout<<p->data<<std::endl;

	NODE n2 = {2};
	NODE n3 = {3};
	NODE n4 = {4};
	NODE n5 = {5};

	n1.next = &n2;
	n2.next = &n3;
	n3.next = &n4;
	n4.next = &n5;
	n5.next = 0;
	//12345

	//for (NODE* p = &n1; p; p = p->next)
	//	std::cout<<p->data<<std::endl;

	NODE n6 = {6};
	//162345

	//链表的插入比顺序表快
	n1.next = &n6;
	n6.next = &n2;

	for (NODE* p = &n1; p; p = p->next)
		std::cout<<p->data<<std::endl;

	//链表的删除比顺序表快
	//16345
	n6.next = &n3;
	for (NODE* p = &n1; p; p = p->next)
		std::cout<<p->data<<std::endl;

	system("cls");

	NODE2 nn1 = {1};
	NODE2 nn2 = {2};
	NODE2 nn3 = {3};
	NODE2 nn4 = {4};
	NODE2 nn5 = {5};

	NODE2 head;
	head.next = &nn1;
	head.pre = &nn5;
	nn1.pre = &head; nn1.next = &nn2;
	nn2.pre = &nn1; nn2.next = &nn3;
	nn3.pre = &nn2; nn3.next = &nn4;
	nn4.pre = &nn3; nn4.next = &nn5;
	nn5.pre = &nn4; nn5.next = &head;
	for (NODE2* q = head.next; q != &head; q = q->next)
		std::cout<<q->data<<std::endl;
	for (NODE2* q = head.pre; q != &head; q = q->pre)
		std::cout<<q->data<<std::endl;

	system("pause");
}