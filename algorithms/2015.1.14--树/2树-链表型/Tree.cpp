#include <iostream>
#include "Tree.h"

//创建
TREE createTREE()
{
	TREE tree = (TREE)malloc(sizeof(_TREE));
	tree->parent = tree->left_child = tree->right_brother = 0;
	return tree;
}
//断开树和其父节点的关系
TREE cutTREE(TREE tree)
{
	if(tree->parent)
	{
		if(tree->parent->left_child == tree)
			tree->parent->left_child = tree->right_brother;
		else
		{
			TREE p = tree->parent->left_child;
			while(p->right_brother != tree)
			{
				p = p->right_brother;
			}
			p->right_brother = tree->right_brother;
		}
		tree->right_brother = tree->parent = 0;
	}
	return tree;
}
//插入
void insertTREE(TREE tree1,TREE tree2)
{
	cutTREE(tree2);
		
	
}
///
static void _deleteTREE(TREE tree)
{
	if(tree)
	{
		
	}
}

//删除
void deleteTREE(TREE tree)
{
	cutTREE(tree);
	_deleteTREE(tree);
}
//数量
int countTREE(TREE tree)
{
	if(tree)
	{
		
	}
	return 0;
}
//高度
int heigthTREE(TREE tree)
{
	if(tree)
	{
		
	}
	return 0;
}