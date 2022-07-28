#include <iostream>
using namespace std;
void main()
{
	 int a[5];
	 int b[5];
	 int i,j,t,m;
	 bool x;
	 bool y;
	 
	 do
	 {
	 cout<<"请从小到大输入5个整数"<<endl;
	 for(i=0;i<5;i++)
	 {
		 cout<<"请输入第一个数组的第"<<i<<"个元素（整数）：";
			 cin>>a[i];
	 }
	 
	 
	 for(i=0;i<4;i++)
	 {
	 if(a[i]>a[i+1])
	 {
	
		 cout<<"数组不是从小到大，请重新输入"<<endl;
	     x=true;
		 system("pause");
	     system("cls");
		 break;
	 }
	 else
	 {   
		 x=false;
 
	 }
	 }
	 }
	 while(x);
	 
	 
	//-------------------------------
	 
	 
	 do
	 {
	cout<<"请从小到大输入5个整数"<<endl;
	  for(i=0;i<5;i++)
	 {
		 cout<<"请输入第二个数组的第"<<i<<"个元素（整数）：";
			 cin>>b[i];
	 }


	  for(i=0;i<4;i++)
	 {
	 if(b[i]>b[i+1])
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




	  //-------------------------------
	  cout<<"两个数组的共同排序大小为："<<endl;

     for(j=0;j<5;j++)
	 {
		 for(i=0;i<5;i++)
		 {
			 if(a[j]>b[i])
			 {
				 t=a[j];
				 a[j]=b[i];
				 b[i]=t;
			 }
		 }
	 }
	 for(m=0;m<4;m++)
	 {
		 for(i=0;i<4-m;i++)
		 {
			 if(b[i]>b[i+1])
			 {
				 t=b[i];
				 b[i]=b[i+1];
				 b[i+1]=t;
			 }
		 }
	 }
	 for(i=0;i<5;i++)
	 {

	 cout<<a[i]<<" ";
	 }
	  for(i=0;i<5;i++)
	 {

	 cout<<b[i]<<" ";
	 }

	system("pause");
}