#include<iostream>
#include "SqList.h"
//创建
//插入
//删除
//查找
//清空

bool xiangdeng(int,int);
bool great(int ,int);

void main()
{
	SQLIST sqlist = createSQLIST();
	
	//操作表我们只能用标准操作函数来操作，而不能
	//打开表操作
	//std::cout<<sqlist->length<<std::endl;
	
	std::cout<<lengthSQLIST(sqlist)<<std::endl;

	//sqlist->data[0] = 1;
	std::cout<<"推入"<<std::endl;
	pushSQLIST(sqlist,1);
	pushSQLIST(sqlist,2);
	pushSQLIST(sqlist,3);
	pushSQLIST(sqlist,4);
	pushSQLIST(sqlist,5);
	pushSQLIST(sqlist,7);
	pushSQLIST(sqlist,6);

	std::cout<<lengthSQLIST(sqlist)<<std::endl;
	
	for(int i = 0; i < lengthSQLIST(sqlist); ++i)
	{
		std::cout<<*getSQLIST(sqlist,i)<<std::endl;
	}
	
	std::cout<<"删除"<<std::endl;
	eraseSQLIST(sqlist,3);
	
	for(int i = 0; i < lengthSQLIST(sqlist); ++i)
	{
		std::cout<<*getSQLIST(sqlist,i)<<std::endl;
	}
	std::cout<<"查找"<<std::endl;
	std::cout<<findSQLIST(sqlist,3,0,xiangdeng)<<std::endl;
	
	std::cout<<"降序"<<std::endl;
	sortSQLIST(sqlist,false,great);
	for(int i = 0; i < lengthSQLIST(sqlist); ++i)
	{
		std::cout<<*getSQLIST(sqlist,i)<<std::endl;
	}
	std::cout<<"清空"<<std::endl;
	clearSQLIST(sqlist);
	std::cout<<lengthSQLIST(sqlist)<<std::endl;

	destroySQLIST(sqlist);

	system("pause");
}

bool xiangdeng(int a,int b)
{
	return a == b;
}
bool great(int a,int b)
{
	return a > b;
}