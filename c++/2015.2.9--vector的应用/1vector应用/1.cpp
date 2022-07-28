#include <iostream>
#include <vector>

void main()
{
	std::vector <int> aa;
	std::vector <int>::iterator  aiter;
	aa.push_back(2);
	aa.push_back(4);
	aa.push_back(2);
	aa.push_back(4);
	aa.push_back(2);
	aa.push_back(4);
	aa.push_back(2);
	aa.push_back(2);
	aa.push_back(2);
	aa.push_back(4);

	aa.push_back(4);
	aa.push_back(4);

	//for(int i = 0; i < aa.size(); ++i)
	//	std::cout<<aa.at(i)<<std::endl;

	for(aiter = aa.begin(); aiter != aa.end(); ++aiter)
		std::cout<<*aiter<<std::endl;

	std::cout<<std::endl;
	aa.erase(aa.begin() + 1);

	for(aiter = aa.begin(); aiter != aa.end(); ++aiter)
		std::cout<<*aiter<<std::endl;
	system("pause");
}