#include <iostream>
#include <vector>
#include <list>
#include "my_vector.h"

struct ABC
{
	int a, b, c;
	ABC(int x = 0, int y = 0, int z = 0)
	{
		a = x;
		b = y;
		c = z;
	}
};

void main()
{
	my_vector<ABC> v1;

	v1.push_back(ABC(1, 2, 3));
	v1.push_back(ABC(2, 3, 4));
	v1.push_back(ABC(3, 4, 5));
	v1.push_back(ABC(4, 5, 6)); //[begin:123][234][345][456][end]

	my_vector<ABC>::iterator it;
	for (it = v1.begin(); it != v1.end(); it++)
		std::cout<<it->a<<"-"<<it->b<<"-"<<it->c<<std::endl;

	my_vector<ABC>::iterator it2 = v1.insert(it, ABC(5, 6, 7));
	//[begin:123][234][345][456][567][end]

	for (it2 = v1.begin(); it2 != v1.end(); )
	{
		if (it2->a == 3)
			it2 = v1.erase(it2);
		else
			++it2;
	}
	//[begin:123][234][456][567][end]

	std::cout<<std::endl;

	for (it = v1.begin(); it != v1.end(); it++)
		std::cout<<it->a<<"-"<<it->b<<"-"<<it->c<<std::endl;

	std::cout<<std::endl;

	v1.insert(v1.begin() + 2, ABC(6, 7, 8));
	//[begin:123][234][678][456][567][end]
	for (it = v1.begin(); it != v1.end(); it++)
		std::cout<<it->a<<"-"<<it->b<<"-"<<it->c<<std::endl;

	system("pause");
}