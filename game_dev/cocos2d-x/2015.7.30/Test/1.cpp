#include "Tree.h"
#include <iostream>

void main()
{
	TN* n0 = createTN(); n0->data = "0";
	TN* n1 = createTN(); n1->data = "1";
	TN* n2 = createTN(); n2->data = "2";
	TN* n3 = createTN(); n3->data = "3";
	TN* n4 = createTN(); n4->data = "4";
	TN* n5 = createTN(); n5->data = "5";
	TN* n6 = createTN(); n6->data = "6";
	TN* n7 = createTN(); n7->data = "7";
	TN* n8 = createTN(); n8->data = "8";
	TN* n9 = createTN(); n9->data = "9";
	insertTN(n0, n1);
	insertTN(n0, n2);
	insertTN(n0, n3);
	insertTN(n2, n4);
	insertTN(n2, n5);
	insertTN(n3, n6);
	insertTN(n6, n7);
	insertTN(n6, n8);
	insertTN(n6, n9);

	preTN(n0); std::cout<<std::endl;
	postTN(n0); std::cout<<std::endl;

	system("pause");
}