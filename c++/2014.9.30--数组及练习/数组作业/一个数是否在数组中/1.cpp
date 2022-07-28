#include <iostream>
using namespace std;
void main()
{
	 int a[10];
	 int i,j,t;
	 bool x=true;
	 bool y;
	 do
	 {
	 cout<<"请从小打到输入十个整数"<<endl;
	 for(i=0;i<10;i++)
	 {
		 cout<<"请输入数组的第"<<i<<"个元素（整数）：";
			 cin>>a[i];
	 }
	  for(i=0;i<4;i++)
	 {
	 if(a[i]>a[i+1])
	 {
	
		 cout<<"数组不是从小到大，请重新输入"<<endl;
	     y=true;
		 system("pause");
	     system("cls");
		 break;
	 }
	 else
	 {   
		 y=false;
 
	 }
	 }
	 }
	 while(y);





	 //----------------
	 cout<<"请任意输一个整数："<<endl;
	 cin>>j;

	 for(i=0;i<10;i++)
	 {

	 if(j==a[i])
	 {
		 x=false;
		 break;
	 }
	 
	
	 }
	 if(x)
	 {
		 cout<<j<<"没有出现在数组中"<<endl;
	 }
	 else
	 {
		  cout<<j<<"出现在数组中"<<endl;
	 }


	


	system("pause");
}