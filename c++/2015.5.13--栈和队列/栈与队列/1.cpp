#include <iostream>
#include "Stack.h"
#include "Queue.h"

void main()
{
	CQueue<int> s1;
	s1.Enter(1);
	s1.Enter(2);
	s1.Enter(3);
	s1.Enter(4);
	s1.Enter(5);
	CQueue<int> s2 = s1;
	s1 = s2;
	while (s1.Size() > 0)
	{
		int x;
		s1.Quit(&x);
		std::cout<<x<<std::endl;
	}

	system("pause");
}