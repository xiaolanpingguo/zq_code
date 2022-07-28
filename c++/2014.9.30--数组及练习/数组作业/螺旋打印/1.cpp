#include <iostream>
using namespace std;
void main()
{
	/*----数列通项公式
	0  1  10  27----4*n*n-11*n+7// 1

    0  2  12  30----4*n*n-10*n+6// 2

    0  3  14  33----4*n*n-9*n+5//  3

    0  4  16  36----4*n*n-8*n+4//  4

    0  5  18  39----4*n*n-7*n+3//  5

    0  7  22  45----4*n*n-5*n+1//  6

    0  8  24  48----4*n*n-4*n+0//  7
*/
	int a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z,num1,num2,temp,qing;
	int a1,b1,c1,d1,e1,f1,g1,h1,i1,j1,k1,l1,m1,n1,o1,p1,q1,r1,s1,t1,u1,v1,w1,x1,y1,z1;

	//判断输入
	do{
	cout<<"请输入第一个数"<<endl;
	cin>>num1;
	cout<<"请输入第二个数"<<endl;
	cin>>num2;
	if(num1>num2)
	{
		temp=num2;
		num2=num1;
		num1=temp;
	}
	
	if(num1<0||num2>99)
	{
		cout<<"输出的数要在0~99之间，请重新输入"<<endl;
		system("pause");
		system("cls");
		
	}
	}
		while(num1<0||num2>99);

	//----输出第一行的黑框
	for(w=1;w<=11;w++)  
	{
	cout<<"■"<<" ";
	}
	cout<<endl;


	for(qing=num1;qing<=num2;qing++)
	{
		system("cls");


	//------图形上半部分开始-----
for(x=6,a=5,n=5,d1=4;n>=1;n--)    //  n：上半部分行数
{
	cout<<"■"<<" ";     //输出每一列第一个黑框

		for(e=5-n,c=a;i=4*c*c-7*c+3+n-1+num1,e>0;e--,c--)   //第一部分--a：数列5的第五项   c：项数依次递减  e:输出的个数
		{                                                   //num1：在输出的数+num1，使从nmu1开始循环打印，以下同理
			if(n==5)                    //当n等于5时，不输出数字，以下同理
			{
				break;	
			}
			
			/*	if( i>num2)              //当输出的数大于num2时，输出黑框，以下同理
			{
				cout<<"■"<<" ";
			}
				
				
				else if(i<10)              //当输出的数小于10时，前面加0，以下同理
				{
			
					cout<<"0"<<i<<" ";
				}
			
			
			
			else                      //当以上条件都不符合时，输出数字，以下同理
			{
				
				cout<<i<<" ";
				
			}*/
			//---------------分割线，上部为不加清屏，下面是加了清屏后的代码，接下来的各部分同理
			if(i<=qing)
			{
				 if(i<10)              
			{
			
				cout<<"0"<<i<<" ";
			}
				else
					cout<<i<<" ";
			}
			else
			{
				cout<<"■"<<" ";
			}


			
			
			
		}


		for(b=1,i=4*n*n-5*n+1-(n-1)+num1;i<=4*n*n-5*n+1+n+1+num1,b<=2*n;i++,b++)//第二部分  //--n：数列6的项数  b:输出每行的个数
		{
			
			
			
				/*if( i>num2)
			{
				cout<<"■"<<" ";
			}
				
			else if(i<10)
			{
			
				cout<<"0"<<i<<" ";
			}
			
			
			
			else
			{
				cout<<i<<" ";
			}*/
			if(i<=qing)
			{
				 if(i<10)              
			{
			
				cout<<"0"<<i<<" ";
			}
				else
					cout<<i<<" ";
			}
			else
			{
				cout<<"■"<<" ";
			}

			
			
			
		}

		
	for(z=5-n,x=n+2,y=1-n;i=4*x*x-11*x+7+y+num1,z>0;z--,x++)//第三部分  //--x：数列1的项数，与行数n有2的加法关系   z:输出的个数
	{

	

			
		if(n==5)
		{
			break;
		}
			/*if( i>num2)
			{
				cout<<"■"<<" ";
			}
				
			else if(i<10)
			{
			
				cout<<"0"<<i<<" ";
			}
			
			
			
			else
			{
				
                 cout<<i<<" ";
			}*/
		if(i<=qing)
			{
				 if(i<10)              
			{
			
				cout<<"0"<<i<<" ";
			}
				else
					cout<<i<<" ";
			}
			else
			{
				cout<<"■"<<" ";
			}
			
	
	}

	
		
		cout<<endl;
		}

//---------------------------分割线
//下半部分

for(p1=5,a1=2,h1=3,m1=8,n1=5;n1>=1;n1--,m1++,a1++,h1++)//m1:第二部分每行的个数,c1,h1代表第一三部分每列的变化
{
	cout<<"■"<<" ";

	for(e1=n1-2,b1=p1,d1=6-n1;i=4*b1*b1-7*b1+3-d1+num1,e1>0;b1--,e1--)//第一部分---//b1：数列5的项数，依次递减  e:输出的个数  d1:输出的数和每项的数的关系
	{
		
		
			
		if(n1==2||n1==1)
		{
			break;
		}
			/*if( i>num2)
			{
				cout<<"■"<<" ";
			}
				
			else if(i<10)
			{
			
				cout<<"0"<<i<<" ";

			}
			
			
			
			else
			{
				
	         cout<<i<<" ";
			}*/
		if(i<=qing)
			{
				 if(i<10)              
			{
			
				cout<<"0"<<i<<" ";
			}
				else
					cout<<i<<" ";
			}
			else
			{
				cout<<"■"<<" ";
			}
			
		
	}

	
	for(k1=m1-n1,i=4*a1*a1-9*a1+5+a1-1+num1;i>=4*a1*a1-9*a1+5-a1+1+num1,k1>0;k1--,i--)//第二部分----//a1：数列3的项数  i：在输出的项数左右打印   k1:输出的个数
	{
	
			
		if(k1==11)                                           //当n1等于1时，k1等于11，输出11个数，不符合要求，因此要实现跳转
		{

			continue;

		}
			
			/*if( i>num2)
			{
				cout<<"■"<<" ";
			}
				
			else if(i<10)
			{
			
				cout<<"0"<<i<<" ";
			}
			
			
			
			else
			{
				
				 cout<<i<<" ";
			}*/
		if(i<=qing)
			{
				 if(i<10)              
			{
			
				cout<<"0"<<i<<" ";
			}
				else
					cout<<i<<" ";
			}
			else
			{
				cout<<"■"<<" ";
			}
			
		
	}


	for(f1=6-n1,g1=n1-1,c1=h1;i=4*c1*c1-11*c1+7+f1+num1,g1>0;g1--,c1++)//第三部分---//  c1：数列1的项数，项数依次递增输出 f1：项数输出的数每列之间的变化   g1:输出的个数
	{
		
		if(n1==1)
		{
			break;

		}
			/*if( i>num2)
			{
				cout<<"■"<<" ";
			}
			
				

			else if(i<10)
			{
			
				cout<<"0"<<i<<" ";
			}
			
			
			
			else
			{
				
				cout<<i<<" ";
			}*/
		if(i<=qing)
			{
				 if(i<10)              
			{
			
				cout<<"0"<<i<<" ";
			}
				else
					cout<<i<<" ";
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