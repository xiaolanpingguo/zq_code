#include <coroutine>
#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <filesystem>
#include <variant>
#include <fstream>


template<typename T>
struct Lazy {
public:
	struct promise_type;
	Lazy(std::coroutine_handle<promise_type> handle)
		: m_handle(handle) {
		std::cout << "Construct a sync object" << std::endl;
	}

	~Lazy() {
		std::cout << "Destruct a sync object " << std::endl;
		m_handle.destroy();
	}

	T get() {
		std::cout << "Coroutine resummed.." << std::endl;
		m_handle.resume();
		return m_handle.promise().value;
	}

	struct promise_type {
		T value = {};
		promise_type() {
			std::cout << "Promise created" << std::endl;
		}
		~promise_type() {
			std::cout << "Promise died" << std::endl;
		}

		/*
			通过这个来和caller进行通信，协程的协程帧就是std::coroutine_handle
		*/
		auto get_return_object() {
			return Lazy<T>{ std::coroutine_handle<promise_type>::from_promise(*this) };
		}

		/*
			如果返回std::suspend_never就表示不暂停协程，会继续执行协程函数体(coroutine body)，
			如果返回的是std::suspend_always就表示创建协程后暂停它，不会去执行coroutine body，程序的执行返回到caller那里。
		*/
		auto initial_suspend() {
			std::cout << "Started the coroutine" << std::endl;
			return std::suspend_always{};
		}
	
		/*
			return_value或者return_void，这两个方法只允许存在一个，用来保存协程的返回值(如果有返回值的话), 
			如果协程是void没有返回值，那么就需要定义return_void，如果有返回值那么就定义return_value。
			编译器会做编译期检查看看是否匹配这两个方法之一，否则会报编译错误
		*/
		void return_value(T v) {
			std::cout << "Got coroutine result " << v << std::endl;
			value = v;
		}

		/*
			表示协程已经执行完了，如果final_suspend返回std::suspend_never表示不暂停协程，
			那么协程就会自动销毁，先后销毁promise, 协程帧上得参数和协程帧；如果返回std::suspend_always则不会自动销毁协程，需要用户手动去删除协程。
		*/
		auto final_suspend() noexcept {
			std::cout << "Finished the coroutine" << std::endl;
			return std::suspend_always{};
		}

		/*
			如果协程发生异常的处理
		*/
		void unhandled_exception() {
			std::exit(1);
		}
	};

	std::coroutine_handle<promise_type> m_handle;
};

Lazy<int> my_coroutine()
{
	/*
		实际上当一个函数是一个协程是，编译器会为这个函数添加以下东西:

			Allocate a coroutine frame;
			Copy any function parameters to the coroutine frame;
			Call the constructor for the promise object of type;
			Call the promise.get_return_object();
			co_await promise.initial_suspend();
		try
		{
			co_return 42; //coroutine body
		}
		catch (...)
		{
			promise.unhandled_exception();
		}
		FinalSuspend:
			co_await promise.final_suspend();
			destruct promise p
			destruct parameters in coroutine frame
			destroy coroutine state
	*/
	std::cout << "Execute the coroutine function body" << std::endl;
	co_return 52;
}

void testCoroutineWithLazy()
{
	std::cout << "----testCoroutineWithLazy Begin -----" << std::endl;
	/*
	
	在第一个例子中，协程是一个立即返回的协程，但是大部分情况，我们都需要自己去控制协程的暂停和恢复，
	不然我们还用协程干什么呢

	于是在这个例子中，我们实现一个我们自己控制的一个协程，我们把协程开始和结束的状态是设置成suspend_always，
	然后在caller调用get()的时候我们恢复协程

	  下面的协程执行完后，打印的结果:
	  ----testCoroutineWithLazy Begin -----
		Promise created
		Construct a sync object
		Started the coroutine
		Created a coroutine
		Coroutine resummed..
		Execute the coroutine function body
		Got coroutine result 52
		Finished the coroutine
		The coroutine result: 52
		----testCoroutineWithLazy End -----
		Destruct a sync object
		Promise died
	*/
	auto coro = my_coroutine();
	std::cout << "Created a coroutine" << std::endl;
	auto result = coro.get();
	std::cout << "The coroutine result: " << result << std::endl;

	std::cout << "----testCoroutineWithLazy End -----" << std::endl;
}