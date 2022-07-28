#include <iostream>

void main()
{
	char s[256];
	std::cin>>s;
	int Len = 0;
	//for(Len = 0; s[Len] != 0;Len++)
	//	;
	while(s[Len] != 0)
	{
		Len++;
	}
	std::cout<<Len<<std::endl;
	
	system("pause");
}