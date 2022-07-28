#include<iostream>

int GetJieCheng(int a)
{
	if(a <= 0)
		return 0;
	int temp = 1;
	for(int i = 1; i <= a; ++i)
		temp *= i;
	return temp;
}

void main()
{
	int x = GetJieCheng(0);
	system("pause");
}