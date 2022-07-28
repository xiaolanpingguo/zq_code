#include <iostream>
#include "Tree.h"

void main()
{
	_TREE_NODE<int>* tn1 = createTN<int>(); tn1->data = 1;
	_TREE_NODE<int>* tn2 = createTN<int>(); tn2->data = 2;
	_TREE_NODE<int>* tn3 = createTN<int>(); tn3->data = 3;
	_TREE_NODE<int>* tn4 = createTN<int>(); tn4->data = 4;
	_TREE_NODE<int>* tn5 = createTN<int>(); tn5->data = 5;
	_TREE_NODE<int>* tn6 = createTN<int>(); tn6->data = 6;
	_TREE_NODE<int>* tn7 = createTN<int>(); tn7->data = 7;

	insertTN(tn1, tn2);
	insertTN(tn1, tn3);
	insertTN(tn1, tn4, false);
	insertTN(tn2, tn5);
	insertTN(tn5, tn6);
	insertTN(tn5, tn7);

	eraseTN(tn2);

	system("pause");
}