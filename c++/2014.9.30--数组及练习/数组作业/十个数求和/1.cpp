#include <iostream>
using namespace std;
void main()
{
	 int a[10];
	 int i,j,t;
	 int sum =0;
	 for(i=0;i<10;i++)
	 {
		 cout<<"请输入数组的第"<<i<<"个元素（整数）：";
			 cin>>a[i];
	 }
	/* for(j=0;j<10;j++)
	 {
		 for(i=0;i<9-j;i++)
		 {
			 if(a[i]>a[i+1])
			 {
				 t=a[i];
				 a[i]=a[i+1];
				 a[i+1]=t;
			 }
		 }
	 }*/
	for(i=0;i<10;i++)
	{
		sum+=a[i];
	}
	cout<<"十个数的和为："<<sum<<endl;



	system("pause");
}