#include <iostream>
#include <chrono>
#include <typeinfo>
#include <ratio>
#include <ctime>
#include <iomanip>
using namespace std;
using namespace std::chrono;


int main()
{
	// 一.时钟周期
	// ratio表示一个时钟周期，比如
	// std::chrono::duration<int, ratio<1, 1>> t1(10)
	// 就代表一个时钟周期为10秒，可以用t1.count()获得
	// 而下面的代码实现的就是先获得系统的时间点，然后按照一个时钟周期
	// 转换成时间点，然后time_since_epoch()用来获得19700101到这个时间点经过
	// 的时钟周期，所以下面两个输出肯定是一样的
	using days_type = std::chrono::duration<int, ratio<1, 1>>;
	time_point<system_clock, days_type> today = time_point_cast<days_type>(system_clock::now());
	cout << today.time_since_epoch().count() << endl;
	cout << time(0) << endl;


	// 二.time_point和time_t的相互转换
	// 时间点还可以进行运算，下面的例子输出前一天和后一天的的日期
	std::chrono::system_clock::time_point now = std::chrono::system_clock::now();

	// typedef hours = std::chrono::duration<int, ratio<3600>>
	// system_clock::from_time_t是time_t到time_point的转换
	time_t last = system_clock::to_time_t(now - hours(24));
	time_t next = system_clock::to_time_t(now + hours(24));
	// "%F %T" 或者 %Y-%m-%d %X 或者 %Y-%m-%d %H.%M.%S  
	cout << "last: " << std::put_time(std::localtime(&last), "%Y-%m-%d %X") << endl;
	cout << "next: " << std::put_time(std::localtime(&next), "%F %T") << endl;


	// 三.获得程序运行的间隔时间
	// system_clock:真实世界的挂钟时间，具体时间依赖于系统
	// steady_clock:不能被调整的时钟，获取稳定的时间间隔，不会因为修改了系统时间而改变
	// high_resolution_clock:高精度时钟，实际上是system_clock或steady_clock的别名
	// 以上3个类型都可以通过now()来获得当前的时间点
	system_clock::time_point t1 = system_clock::now();
	cout << "hello world" << endl;
	system_clock::time_point t2 = system_clock::now();
	cout << (t2 - t1).count() << endl;
	cout << duration_cast<microseconds>(t2 - t1).count() << endl;
	cout << duration_cast<milliseconds>(t2 - t1).count() << endl;
	cout << duration_cast<seconds>(t2 - t1).count() << endl;
	
				/*std::chrono::system_clock::time_point now_nano = std::chrono::system_clock::now();
			INT64 score = std::chrono::duration_cast<std::chrono::nanoseconds>(now_nano.time_since_epoch()).count();*/
	
#ifdef WIN32
	system("pause");
#endif
	return 0;
}