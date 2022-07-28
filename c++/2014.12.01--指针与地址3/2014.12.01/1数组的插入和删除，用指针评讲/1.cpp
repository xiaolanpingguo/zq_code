#include<iostream>

void main()
{
	int a[10],b = 5;
	for(int i = 0; i < b; ++i)
	{
		std::cin>>*(a + i);
		//a[i]
		//(a + i)[0]
	}

	while(1)
	{
		system("cls");
		for(int i = 0; i < b; ++i)
		{
			std::cout<<"("<<*(a + i)<<")";
		}
		for(int i = b; i < 10; ++i)
		{
			std::cout<<"( )";
		}
		std::cout<<"\1)插入\n2)删除\n3)退出\n请选择:";
		int sel;
		std::cin>>sel;
		if(sel == 1)
		{
			if(b == 10)
				std::cout<<"数组已满不能插入";
			else
			{
				int c,d;
				do
				{
					std::cin>>c>>d;
				}while(d < 0 || d > b);
				
				//获得需要移动的次数
				int m = b - d;
				for(int i = 0; i < m; ++i)
				{//依次后移
					*(a + b - i) = *(a + b - 1 - i);
				}
				*(a + d) = c;//放入数据
				b++;//长度加1
				std::cout<<"插入成功";
			}
			system("pause");
		}
		else if(sel == 2)
		{
			if(b == 0)
				std::cout<<"数组已空";
			else
			{
				int d;
				do
				{
					std::cin>>d;
				}while(d < 0||d >= b);
				//得到移动次数
				int m = b - d - 1;
				//依次移位
				for(int i = 0; i < m; ++i)
					*(a + d + i) = *(a + d + 1 + i);
				b--;//长度递减
				std::cout<<"删除成功";
			}
			system("pause");
		}
		else if(sel == 3)
			break;
	}
	system("pause");
}