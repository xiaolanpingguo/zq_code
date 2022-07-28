#include<iostream>

void main()
{
	int a;
	std::cin>>a;
	int b[10];
	bool shengxu = false;
	do
	{
		shengxu = false;
		for(int i = 0; i < 10; ++i)
		{
			std::cin>>b[i];
		}
		for(int i = 0; i < 9; ++i)
		{
			if(b[i]>b[i + 1])
			{
				shengxu = true;
				break;
			}
		}
	}while(shengxu);

	int begin = 0;
	int end = 9;
	int mid;
	bool have = false;
	while(begin <= end)
	{
		mid = (end + begin)/2;
		if(a < b[mid])
		{
			end = mid - 1;
		}
		else if(a > b[mid])
		{
			begin = mid + 1;
		}
		else
		{
			have = true;
			break;
		}
	}

	if(have)
	{
		std::cout<<"сп"<<std::endl;
	}
	else
	{
		std::cout<<"ц╩сп"<<std::endl;
	}

	system("pause");
}