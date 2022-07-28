#include <iostream>

class 变长数组
{
	int* p;
	int n;
public:
	变长数组(int num)
	{
		n = num;
		p = new int[n];
	}

	变长数组(const 变长数组& that)
	{
		n = that.n;
		p = new int[n];
		for(int i = 0; i < n; ++i)
			p[i] = that.p[i];
	}

	变长数组& operator = (const 变长数组& that)
	{
		if(this != &that)
		{
			delete []p;
			p = new int[n = that.n];
			for(int i = 0; i < n; ++i)
				p[i] = that.p[i];
		}
		return *this;
	}

	~变长数组()
	{
		delete []p;
	}

	bool 设置(int pos,int value)
	{
		if(pos < 0 || pos >= n)
			return false;

		p[pos] = value;
		return true;
	}

	int* 获取(int pos)
	{
		return (pos < 0 || pos >= n) ? 0 : p + pos; 
	}
};

void main()
{
	变长数组 a(5);
	for(int i = 0; i < 5; ++i)
		a.设置(i,i);
	变长数组 a1 = a;
	for(int i = 0; i < 5; ++i)
		std::cout<<*(a1.获取(i))<<std::endl;
	system("pause");
}