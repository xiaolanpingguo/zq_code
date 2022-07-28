#include "BinaryTree.h"
#include <iostream>

//创建
BINARYTREE createBINARYTREE()
{
	BINARYTREE tree = (BINARYTREE)malloc(sizeof(_BINARY_TREE));
	tree->parent = tree->left = tree->right = NULL;
	return tree;
}

//断开其与其父节点的联系
BINARYTREE cutBINARYTREE(BINARYTREE bt)
{
	if(bt && bt->parent)
	{
		if(bt->parent->left == bt)
			bt->parent->left = 0;
		if(bt->parent->right == bt)
			bt->parent->right = 0;
		bt->parent = 0;
	}
	return bt;
}

//插入:将bt2插入bt1，left为真插左边，假插右边
BINARYTREE insertBINARYTREE(BINARYTREE bt1,BINARYTREE bt2,bool left)
{
	BINARYTREE p = 0;
	if(bt1)
	{
		cutBINARYTREE(bt2);
		if(left)
		{
			p = bt1->left;
			if(p)
				p->parent = 0;
			bt1->left = bt2;
			bt2->parent = bt1;
		}
		else
		{
			p = bt1->right;
			if(p)
				p->parent = 0;
			bt1->right = bt2;
			bt2->parent = bt1;
		}
	}
	return p;
}

void _deleteBINARYTREE(BINARYTREE bt)
{
	if(bt)
	{
		_deleteBINARYTREE(bt->left);
		_deleteBINARYTREE(bt->right);
		free(bt);
	}
}

//删除
void deleteBINARYTREE(BINARYTREE bt)
{
	cutBINARYTREE(bt);
	_deleteBINARYTREE(bt);
}

//数量
int  countBINARYTREE(BINARYTREE bt)
{
	if(bt)
	{
		return 1 + countBINARYTREE(bt->left) + countBINARYTREE(bt->right);
	}
	return 0;
}

//高度
int heightBINARYTREE(BINARYTREE bt)
{
	if(bt)
	{
		int l_h = heightBINARYTREE(bt->left);
		int r_h = heightBINARYTREE(bt->right);
		return ((l_h > r_h)? l_h:r_h) + 1;
	}
	return 0;
}

//前序--递归
void recursion_pre_travelBINARYTREE(BINARYTREE bt)
{
	if(bt)
	{
		std::cout<<bt->data<<std::endl;
		recursion_pre_travelBINARYTREE(bt->left);
		recursion_pre_travelBINARYTREE(bt->right);
	}
}
//中序
void recursion_mid_travelBINARYTREE(BINARYTREE bt)
{
	if(bt)
	{
		recursion_pre_travelBINARYTREE(bt->left);
		std::cout<<bt->data<<std::endl;
		recursion_pre_travelBINARYTREE(bt->right);
	}
}
//后续
void recursion_post_travelBINARYTREE(BINARYTREE bt)
{
	if(bt)
	{
		recursion_pre_travelBINARYTREE(bt->left);
		recursion_pre_travelBINARYTREE(bt->right);
		std::cout<<bt->data<<std::endl;
	}
}

//前序---非递归
void pre_travelBINARYTREE(BINARYTREE bt)
{
	BINARYTREE stack[256];
	int top= 0;
	stack[top++] = bt;
	while(top != 0)
	{
		BINARYTREE q = stack[--top];
		std::cout<<q->data<<std::endl;
		if(q->right)
			stack[top++] = q->right;
		if(q->left)
			stack[top++] = q->left;
	}	
}
//中序
void mid_travelBINARYTREE(BINARYTREE bt)
{
	BINARYTREE stack[256];
	int top= 0;
	if(bt->right)
		stack[top++] = bt->right;
	stack[top++] = bt;
	if(bt->left)
		stack[top++] = bt->left;
	while(top != 0)
	{
		BINARYTREE q = stack[--top];
		if(q->right)
			stack[top++] = q->right;
		stack[top++] = q;
		if(q->left)
			stack[top++] = q->left;
	}
}
//后序
void post_travelBINARYTREE(BINARYTREE bt);

//层序--非递归
void level_travelBINARYTREE(BINARYTREE bt);