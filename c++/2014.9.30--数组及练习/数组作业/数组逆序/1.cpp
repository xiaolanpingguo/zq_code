#include <iostream>
using namespace std;
void main()
{
	 int a[10];
	 int i,j,t;
	 for(i=0;i<10;i++)
	 {
		 cout<<"请输入数组的第"<<i<<"个元素（整数）：";
			 cin>>a[i];
	 }

	 cout<<"逆序过后十个元素的情况为："<<endl;
	
	  for(i=0;i<10;i++)
	 {
		 cout<<"第"<<i<<"一个元素为"<<a[9-i]<<endl;
			
	 }

	 


	system("pause");
}