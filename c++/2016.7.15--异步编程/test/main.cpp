#include <iostream>   
#include <thread>
#include <future>
using namespace std;

void f(int i)
{
	cout << i << endl;
}

int main() 
{
	//在C11中增加了线程，一般我们是这么用的：
	thread thr(f, 10);
	thr.join();

	//但是，如果我们要获得线程返回的数据呢，这没法办到，
	//但C11还提供了另外的跟线程的类似的异步接口:std::async,
	//std::async会自动创建一个线程去调用线程函数，它返回一个std::future，这个future中存储了线程函数返回的结果
	//在介绍async具体用法以及为什么要用std::async代替线程的创建之前
	//我想先说一说std::future、std::promise和std::packaged_task

	//std::future伪代码
	//deferred：异步操作还没开始
	//ready：异步操作已经完成
	//timeout：异步操作超时
	//std::future_status status;
	//do {
	//	status = future.wait_for(std::chrono::seconds(1));
	//	if (status == std::future_status::deferred) {
	//		std::cout << "deferred\n";
	//	}
	//	else if (status == std::future_status::timeout) {
	//		std::cout << "timeout\n";
	//	}
	//	else if (status == std::future_status::ready) {
	//		std::cout << "ready!\n";
	//	}
	//} while (status != std::future_status::ready);

	//std::promise
	//std::promise为获取线程函数中的某个值提供便利，在线程函数中给外面传进来的promise赋值
	//当线程函数执行完成之后就可以通过promis获取该值了
	//值得注意的是取值是间接的通过promise内部提供的future来获取的，它的基本用法：
	//std::promise<int> pr;
	//std::thread t([](std::promise<int>& p){ p.set_value_at_thread_exit(9); }, std::ref(pr));
	//std::future<int> f = pr.get_future();
	//auto r = f.get();

	//std::packaged_task
	//std::packaged_task它包装了一个可调用的目标(如function, lambda expression, bind expression,or another function object) 
	//以便异步调用，它和promise在某种程度上有点像，promise保存了一个共享状态的值
	//而packaged_task保存的是一个函数。它的基本用法：
	//std::packaged_task<int()> task([](){ return 7; });
	//std::thread t1(std::ref(task));
	//std::future<int> f1 = task.get_future();
	//auto r1 = f1.get();

	//而他们三者的关系是这样的:std::future提供了一个访问异步操作结果的机制，它和线程是一个级别的属于低层次的对象
	//在它之上高一层的是std::packaged_task和std::promise，他们内部都有future以便访问异步操作结果
	//std::packaged_task包装的是一个异步操作，而std::promise包装的是一个值，都是为了方便异步操作的
	//因为有时我需要获取线程中的某个值，这时就用std::promise
	//而有时我需要获一个异步操作的返回值，这时就用std::packaged_task

	//下面来看具体用法：
	//std::launch::async：在调用async就开始创建线程。
	//std::launch::deferred：延迟加载方式创建线程。调用async时不创建线程，直到调用了future的get或者wait时才创建线程。
	std::future<int> f1 = std::async(std::launch::async, [](){
		return 8;
	});

	cout << f1.get() << endl; //output: 8

	std::future<void> f2 = std::async(std::launch::deferred, [](){
		cout << 8 << endl;
	});

	f2.wait(); //output: 8

	std::future<int> future = std::async(std::launch::async, [](){
		std::this_thread::sleep_for(std::chrono::seconds(3));
		return 8;
	});

	std::cout << "waiting...\n";
	std::future_status status;
	do {
		status = future.wait_for(std::chrono::seconds(1));
		if (status == std::future_status::deferred) {
			std::cout << "deferred\n";
		}
		else if (status == std::future_status::timeout) {
			std::cout << "timeout\n";
		}
		else if (status == std::future_status::ready) {
			std::cout << "ready!\n";
		}
	} while (status != std::future_status::ready);

	std::cout << "result is " << future.get() << '\n';

	std::getchar();
	return 0;
}