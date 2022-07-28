#ifndef _BINARY_TREE_H_
#define _BINARY_TREE_H_
#define BTDATA int

typedef struct _BINARY_TREE
{
     BTDATA data;
     _BINARY_TREE* parent;
     _BINARY_TREE* left;
     _BINARY_TREE* right;
}* BINARYTREE;

//创建
BINARYTREE createBINARYTREE();

//断开其与其父节点的联系
BINARYTREE cutBINARYTREE(BINARYTREE bt);

//插入:将bt2插入bt1，left为真插左边，假插右边
BINARYTREE insertBINARYTREE(BINARYTREE bt1,BINARYTREE bt2,bool left);

//删除
void deleteBINARYTREE(BINARYTREE bt);

//数量
int  countBINARYTREE(BINARYTREE bt);

//高度
int heightBINARYTREE(BINARYTREE bt);

//前序--递归
void recursion_pre_travelBINARYTREE(BINARYTREE bt);
//中序
void recursion_mid_travelBINARYTREE(BINARYTREE bt);
//后续
void recursion_post_travelBINARYTREE(BINARYTREE bt);

//前序---非递归
void pre_travelBINARYTREE(BINARYTREE bt);
//中序
void mid_travelBINARYTREE(BINARYTREE bt);
//后序
void post_travelBINARYTREE(BINARYTREE bt);

//层序--非递归
void level_travelBINARYTREE(BINARYTREE bt);

#endif