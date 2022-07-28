#include <iostream>
#include "Astar.h"

void main()
{
	char map[] = 
	{
		1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,0,1,1,1,1,1,
		1,1,1,1,1,0,1,1,1,1,1,
		1,1,1,1,1,0,1,1,1,1,1,
		1,1,1,1,1,0,0,0,0,1,1,
		1,1,1,1,1,1,1,1,0,1,1,
		1,1,1,0,0,0,0,0,0,1,1,
		1,1,1,0,1,1,1,1,1,1,1,
		1,1,1,0,0,0,0,1,1,1,1,
		1,1,1,1,1,1,0,1,1,1,1,
	};
	int path[121];
	int luchang = AStar::FindPath(map,11,11,0,120,path);
	std::cout<<luchang<<std::endl;
	std::cout<<std::endl;

	for(int i = luchang - 1; i >= 0; --i)
		std::cout<<path[i]<<std::endl;
	system("pause");
}