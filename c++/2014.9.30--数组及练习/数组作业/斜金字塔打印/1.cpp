#include <iostream>
using namespace std;
void main()
{
	int a,b,c,d,i,j,x,y,z,m,n,qing;
	  cout<<"请输入一个数"<<endl;
	  cin>>a;

	  for(qing=a;qing>=0;qing--)
	  {
		  system("cls");
	 for(z=2,x=1,i=a;z<=11;i=i-x,x++,z++)
		  
	  {
		  for(c=1,y=z,j=i;y<=11;j=j-y,y++,c++)
		  {
			 
			   if(j>=qing)
			  {
				     if(10>j&&j>=0) 
			  {
				  cout<<"0"<<j<<" ";
			  }

					 else
						 cout<<j<<" ";
			  }
			 
			    else
			  {
				 cout<<"■"<<" ";
			  }
			   
			
		
			 
		  }
		   
		  for(d=c,n=9,m=j+1;d<=10;m=m-n,n--,d++)
		  {
			 if(m>=qing)
			  {
				     if(10>m&&m>=0) 
			  {
				  cout<<"0"<<m<<" ";
			  }

					 else
						 cout<<m<<" ";
			  }
			 
			    else
			  {
				 cout<<"■"<<" ";
			  }

			  
		  }
		  
	  cout<<endl;
	  }
	

	 }
	system("pause");
}