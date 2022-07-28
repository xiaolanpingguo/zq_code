#include <iostream>
#include "Tree.h"

//创建
TREE createTREE(int child_size)
{
	TREE tree = (TREE)malloc(sizeof(_TREE));
	tree->parent = 0;
	tree->child_length = 0;
	tree->child_size = child_size;
	tree->child_data = (TREE*)malloc(sizeof(TREE) * tree->child_size );//?
	return tree;
}
//断开树和其父节点的关系
TREE cutTREE(TREE tree)
{
	if(tree->parent)
	{
		//找到tree在其父节点的位置
		int del = 0;
		for(;del < tree->parent->child_length;++del)
		{
			if(tree == tree->parent->child_data[del])
				break;
		}
		int move = tree->parent->child_length - del - 1;
		for(int j = 0; j < move;++j)
		{
			tree->parent->child_data[del + j] = tree->parent->child_data[del + j + 1];
		}
		tree->parent->child_length -= 1;
		tree->parent = 0;
	}
	return tree;
}
//插入
void insertTREE(TREE tree1,TREE tree2)
{
	cutTREE(tree2);

	if(tree1->child_length == tree1->child_size)
	{
		tree1->child_size *= 2;
		TREE* p = (TREE*)malloc(sizeof(TREE) * tree1->child_size);
		for(int i = 0;i < tree1->child_length;++i)
			p[i] = tree1->child_data[i];
		free(tree1->child_data);
		tree1->child_data = p;
	}

	tree1->child_data[tree1->child_length++] = tree2;
	tree2->parent = tree1;
}
///
static void _deleteTREE(TREE tree)
{
	if(tree)
	{
		for(int i = 0; i < tree->child_length;++i)
		{
			_deleteTREE(tree->child_data[i]);
		}
		free(tree->child_data);
		free(tree);
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
		int  num = 0;
		for(int i = 0; i < tree->child_length;++i)
			num += countTREE(tree->child_data[i]);
		return num + 1;
	}
	return 0;
}
//高度
int heigthTREE(TREE tree)
{
	if(tree)
	{
		int heigth = 0;
		for(int i = 0; i < tree->child_length;++i)
		{
			int child_heigth = heigthTREE(tree->child_data[i]);
			if(heigth < child_heigth)
				heigth = child_heigth;
		}
		return  heigth + 1;
	}
	return 0;
}