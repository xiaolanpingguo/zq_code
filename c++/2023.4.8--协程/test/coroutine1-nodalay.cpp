#include <coroutine>
#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <filesystem>
#include <variant>
#include <fstream>


template<typename T>
struct sync1 {
public:
	struct promise_type;
	sync1(std::coroutine_handle<promise_type> handle)
		: m_handle(handle) {
		std::cout << "Construct a sync object" << std::endl;
	}

	~sync1() {
		std::cout << "Destruct a sync object " << std::endl;
		m_handle.destroy();
	}

	T get() {
		std::cout << "We got the return value..." << std::endl;
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
			return sync1<T>{ std::coroutine_handle<promise_type>::from_promise(*this) };
		}

		/*
			如果返回std::suspend_never就表示不暂停协程，会继续执行协程函数体(coroutine body)，
			如果返回的是std::suspend_always就表示创建协程后暂停它，不会去执行coroutine body，程序的执行返回到caller那里。
		*/
		auto initial_suspend() {
			std::cout << "Started the coroutine" << std::endl;
			return std::suspend_never{};
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

sync1<int> my_coroutine1()
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

void testCoroutineWithNoDalay()
{
	std::cout << "----testCoroutineWithNoDalay Begin -----" << std::endl;
	/*
	
	该例子是一个协程立即返回的例子：

	一个函数体(function body)中含有c++20的三个新增的关键字(co_return, co_yield, co_await)之一，那么这个函数就是一个协程.
	然后编译器规定: co_return的返回对象里必须要有promise_type类型和它的API，就像下面那样:
	struct promise_type {
		  sync<int> get_return_object() { return {}; }
		  std::suspend_never initial_suspend() { return {}; }
		  std::suspend_never final_suspend() noexcept { return {}; }
		  void return_void() {} //注:return_void和return_value二者只允许存在一个
		  void return_value(int val) {
			  //save coroutine return value
		  }
		  void unhandled_exception() { std::terminate(); }
	  ｝

	  C++20的协程难以的理解的原因就在于用户的代码要和编译器一起配合才能完成一个协程
	  一些必要的函数我已经在上面这个测试类加了注释

	  下面的协程执行完后，打印的结果：

		1: Promise created		在协程帧里创建一个promise对象,并拷贝参数到协程帧
		2: Construct a sync object		创建一个协程和caller的通信对象返回给caller
		3: Started the coroutine	立即执行或者在后面执行(根据你的需求)函数体(coroutine body)
		4: Execute the coroutine function body		执行函数体(coroutine body)
		5: Got coroutine result 52		得到协程的返回值
		6: Finished the coroutine		协程已经执行完了
		7: Created a coroutine			回到caller的下一行代码
		8: We got the return value...	called获取协程的返回值
		9: The coroutine result: 52		得到返回值
		10: Destruct a sync object		析构sync对象
		11: Promise died				在sync析构函数里摧毁promise对象(因为这个例子中final_suspend返回的是suspend_always, 因此协程不会自动销毁)
	*/
	auto coro = my_coroutine1();
	std::cout << "Created a coroutine" << std::endl;
	auto result = coro.get();
	std::cout << "The coroutine result: " << result << std::endl;

	std::cout << "----testCoroutineWithNoDalay End -----" << std::endl;
}