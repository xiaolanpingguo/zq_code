#ifndef _TEST_H_
#define _TEST_H_

class CTest
{
public:
	void f1();
	void f2()
	{
	
	}
	inline void f3();
};

//类中的内联函数的定义写在头文件中

inline void CTest::f3()
{

}

#endif