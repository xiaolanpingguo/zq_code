#include <iostream>
#include "FindPath.h"

void main()
{
	char map[]
	=
	{
		1,1,0,1,1,1,1,
		1,1,0,0,1,1,0,
		1,1,0,1,1,0,1,
		1,1,0,1,1,0,0,
		1,1,0,1,1,1,1,
		0,0,1,1,1,1,0
	};
	std::vector<int> path;
	if (FindPathD(map, 7, 6, 29, 28, &path))
	{
		std::cout<<"找到了路：";
		for (int i = 0; i < path.size(); ++i)
			std::cout<<path[i]<<' ';
		std::cout<<std::endl;
	}
	else
		std::cout<<"无路可走：";

	system("pause");
}