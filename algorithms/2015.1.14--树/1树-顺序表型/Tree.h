#ifndef _TREE_SQLIST_H_
#define _TREE_SQLIST_H_

#define TDATA int

typedef struct _TREE
{
	TDATA data;//数据
	_TREE* parent;//父节点指针
	int child_size ;//子节点顺序表容量
	int child_length;//子节点顺序表长度
	_TREE** child_data;//子节点顺序表数据
}* TREE;

//创建
TREE createTREE(int child_size = 4);
//断开树和其父节点的关系
TREE cutTREE(TREE tree);
//插入
void insertTREE(TREE tree1,TREE tree2);
//删除
void deleteTREE(TREE tree);
//数量
int countTREE(TREE tree);
//高度
int heigthTREE(TREE tree);

#endif