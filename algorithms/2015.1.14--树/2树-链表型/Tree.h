#ifndef _TREE_LINKLIST_H_
#define _TREE_LINKLIST_H_

#define TDATA int

typedef struct _TREE
{
	TDATA data;//数据
	_TREE* parent;//父节点指针
	_TREE* left_child;//左孩子指针
	_TREE* right_brother;//右兄弟指针
}* TREE;

//创建
TREE createTREE();
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