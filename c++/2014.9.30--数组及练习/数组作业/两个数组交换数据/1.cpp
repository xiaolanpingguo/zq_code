#include <iostream>
using namespace std;
void main()
{
	 int a[5];
	 int b[5];
	 int i,j,t;
	 for(i=0;i<5;i++)
	 {
		 cout<<"请输入第一个数组的第"<<i<<"个元素（整数）：";
			 cin>>a[i];
	 }
	 for(i=0;i<5;i++)
	 {
		 cout<<"请输入第二个数组的第"<<i<<"个元素（整数）：";
			 cin>>b[i];
	 }
	
	 cout<<"两个数组的数据即将进行交换，按任意键继续："<<endl;
	 system("pause");
	 for(i=0;i<5;i++)
	 {
		 t=a[i];
		 a[i]=b[i];
		 b[i]=t;
	 }
	 cout<<"交换后第一个数组的元素为："<<endl;
	 for(i=0;i<5;i++)
	 {
		 cout<<a[i]<<" ";
	 }
	 cout<<endl;

	 cout<<"交换后第二个数组的元素为："<<endl;
	  for(i=0;i<5;i++)
	 {
		 cout<<b[i]<<" ";
	 }
	  cout<<endl;

	


	system("pause");
}