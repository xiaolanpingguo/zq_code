#include <iostream>
using namespace std;
void main()
{
	 int a[100];
	 int i,j=0,t;
	 cout<<"请输入一个十进制数："<<endl;
	 cin>>i;

	 while(i!=0)
	 {
		 a[j]=i%2;
		 i=i/2;
		 j++;

	 }
	 cout<<"该数的二进制为："<<endl;
	 while(i>0){
	 cout<<a[j-1];
	 j--;
	 }
 /*for(i=j-1;i>=0;i--)
	 {
	 cout<<a[i]<<" ";
	 }*/
cout<<endl;
/*while()
{
	a[j]=i%8;
	i=i/8;
	j++;*/

	system("pause");
}