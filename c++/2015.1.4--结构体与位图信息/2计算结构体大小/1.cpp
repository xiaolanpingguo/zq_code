#include<iostream>


void main()
{
	int a[256],b = 0;
	while(1)
	{
		system("cls");
		std::cout<<"1)char\n2)short\n3)int\n4)double\n5)ÍË³ö\nÇëÑ¡Ôñ";
		int sel;
		std::cin>>sel;
		if(sel >= 1 && sel <= 4)
			a[b++] = sel;
		else if(5 == sel)
			break;
	}

	int bytes = 0;
	int max = 1;
	for(int i = 0; i < b ;++i)
	{
		switch(a[i])
		{
		case 1:
			{
				bytes += sizeof(char);
				if(max < sizeof(char))
					max = sizeof(char);
			}
			break;
		case 2:
			{
				if(bytes % sizeof(short) != 0)
					bytes += (sizeof(short) - bytes % sizeof(short));
				bytes += sizeof(short);
				if(max < sizeof(short))
					max = sizeof(short);
			}
			break;
		case 3:
			{
				if(bytes % sizeof(int) != 0)
					bytes += (sizeof(int) - bytes % sizeof(int));
				bytes += sizeof(int);
				if(max < sizeof(int))
					max = sizeof(int);
			}
			break;
		case 4:
			{
				if(bytes % sizeof(double) != 0)
					bytes += (sizeof(double) - bytes % sizeof(double));
				bytes += sizeof(double);
				if(max < sizeof(double))
					max = sizeof(double);
			}
			break;
		}
	}
	if(bytes % max != 0)
		bytes += (max - bytes % max);
	std::cout<<bytes<<std::endl;
	system("pause");
}

//short <><>
//int   <><><><><><>
//double <><><><><><><><>
//char   <>
//short  <><><><><><><>