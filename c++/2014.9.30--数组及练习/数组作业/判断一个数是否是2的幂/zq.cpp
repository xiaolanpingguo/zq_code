#include <iostream>
using namespace std;
void main()
{
	int b,i,j=0;
	int a[10];
	for(i=0;i<10;i++)
	{
		cout<<"请输入数组的第"<<i<<"个元素"<<endl;
		cin>>a[i];
	}
	for(i=0;i<10;i++)
	{
		if((a[i]&(a[i]-1))==0)
		  j++;
	}
	cout<<"其中是2的幂有"<<j<<"个"<<endl;
	system("pause");
}