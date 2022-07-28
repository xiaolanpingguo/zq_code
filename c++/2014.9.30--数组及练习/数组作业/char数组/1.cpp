#include <iostream>
using namespace std;
void main()
{
	

	int m=0,n=0;
	int i;	
	char a[10];
	for(i=0;i<10;i++)
	{
		cout<<"请输入数组第"<<i<<"个元素："<<endl;
		cin>>a[i];
	}
   for(i=0;i<10;i++)
   {
	   if((int)a[i]>=48&&(int)a[i]<=57)
	   {
		   n++;
	   }
	   if( ((int)a[i]>=65&&(int)a[i]<90)|| ((int)a[i]>=97&&(int)a[i]<=122))
	   {
		   m++;
	   }
   }
   cout<<"其中字母的数量为："<<m<<"个"<<endl;
   cout<<"阿拉伯数字的数量为："<<n<<"个"<<endl;

	 
	

	system("pause");
}