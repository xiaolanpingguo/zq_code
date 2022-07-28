#include<iostream>
#include <math.h>
#include <time.h>
#include "1.h"

float TriangleArea(float x,float y,float x1,float y1,float x2,float y2)
{
	//两点的距离，两边的距离之和小于第三边就不能构成三角形
	if(sqrt((x1 - x)*(x1 - x) + (y1 - y)*(y1 - y)) <= sqrt((x2 - x)*(x2 - x) + (y2 - y)*(y2 - y)))
		return 0.0f;
	//求高
	
 //   float k;
	//float d;
	//float h;
	//k=(y1-y)/(x1-x);//斜率->0值检测
	//d=y1-k*x1;//截距
	//h=（k*x2+y2+d)*(k*x2+y2+d)/(k*k+1);//高
	//float di=sqrt(pow(abs(x1-x),2)+pow(abs(y1-y),2));//底边长度
	//return sqrt(h)/2*di;

	//求三边边长
	float a = sqrt(pow((x-x1),2)+pow((y-y1),2));
	float b = sqrt(pow((x1-x2),2)+pow((y1-y2),2));
	float c = sqrt(pow((x-x2),2)+pow((y-y2),2));
	//得到周长一半
	float z = (a+b+c)/2;
	//得到面积->海伦公式
	return sqrt(z * (z - a) * ( z - c) * ( z - b));
}

int InitRandom()
{
	if(rand() % 2)
		return rand();
	else
		return rand() % rand();
}

int RandomShort(int max,int min)
{
	return rand() % (max - min + 1) + min; 
}

float RandomShort(float max,float min)
{
	return (max - min) * (rand() / 32767.0f) + min;
}

void ArrayRandom(int* MyArray,int begin,int end)
{
	int n  =  end - begin;
	if(n <= 0)
		return;
	if(begin < 0)
		return;
	if(end > 19)
		return;

	for(int i = 0; i < n;++i)
	{
		int j = rand()% (n - i) + begin;
		int a = MyArray[j];
		MyArray[j] = MyArray[end - i];
		MyArray[end - i] = a;
	}
}

void ChineseTime(char* MyArray)
{
	MyArray[0] = 0;
	time_t t = time(0);
	char et[32];
	ctime_s(et,32,&t);
	char nian[4];
	
	memcpy(nian,et + 20,4);
	const char* c_num[]
	=
	{
		"零","一","二","三","四",
		"五","六","七","八","九"
	};
	for(int i = 0; i < 4;++i)
		strcat(et,c_num[nian[i] - '0']);
	strcat(et,"年");
	
	const char* e_month[]
	=
	{
		"Jan","Feb","Mar","Apr","May","Jun",
		"Jul","Aug","Sep","Oct","Nov","Dec"
	};

	const char* c_month[]
	=
	{
		"一月","二月","三月","四月","五月","六月",
		"七月","八月","九月","十月","十一月","十二月"
	};
	char yue[4] = {};
	memcpy(yue,et+4,3);
	for(int i = 0; i < 12;++i)
	{
		if(strcmp(yue,e_month[i]) == 0)
		{
			strcat(et,c_month[i]);
			break;
		}
	}

}
void main()
{
	srand((unsigned int)time(0));
	//float a = TriangleArea(1.0f,1.0f,2.0f,2.0f,3.0f,3.0f);
	for(int i = 0; i < 10; ++i)
	{
		std::cout<<RandomShort(10.9f,2.2f)<<std::endl;
	}
	char nyr[32];
	time_t t = time(0);
	char et[32];
	ctime_s(et,32,&t);
	std::cout<<et<<std::endl;
	//ChineseTime(nyr);
	system("pause");
}