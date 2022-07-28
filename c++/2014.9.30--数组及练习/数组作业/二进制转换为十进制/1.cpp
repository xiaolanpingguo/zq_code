#include <iostream>
#include <cmath>
using namespace std;
void main()
{
	 int a,b=0,n=0,t;
	 cout<<"请输入一个二进制数："<<endl;
	 cin>>a;
	 while(a>0)
	 {
		 t=a%10;
		 a=a/10;
		 b=b+(t*pow(2.0,n));
		 n++;
	 }
		 cout<<"十进制为："<<b<<endl;

		 



	system("pause");
}