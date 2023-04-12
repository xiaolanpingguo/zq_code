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
			ͨ���������caller����ͨ�ţ�Э�̵�Э��֡����std::coroutine_handle
		*/
		auto get_return_object() {
			return sync1<T>{ std::coroutine_handle<promise_type>::from_promise(*this) };
		}

		/*
			�������std::suspend_never�ͱ�ʾ����ͣЭ�̣������ִ��Э�̺�����(coroutine body)��
			������ص���std::suspend_always�ͱ�ʾ����Э�̺���ͣ��������ȥִ��coroutine body�������ִ�з��ص�caller���
		*/
		auto initial_suspend() {
			std::cout << "Started the coroutine" << std::endl;
			return std::suspend_never{};
		}
	
		/*
			return_value����return_void������������ֻ�������һ������������Э�̵ķ���ֵ(����з���ֵ�Ļ�), 
			���Э����voidû�з���ֵ����ô����Ҫ����return_void������з���ֵ��ô�Ͷ���return_value��
			���������������ڼ�鿴���Ƿ�ƥ������������֮һ������ᱨ�������
		*/
		void return_value(T v) {
			std::cout << "Got coroutine result " << v << std::endl;
			value = v;
		}

		/*
			��ʾЭ���Ѿ�ִ�����ˣ����final_suspend����std::suspend_never��ʾ����ͣЭ�̣�
			��ôЭ�̾ͻ��Զ����٣��Ⱥ�����promise, Э��֡�ϵò�����Э��֡���������std::suspend_always�򲻻��Զ�����Э�̣���Ҫ�û��ֶ�ȥɾ��Э�̡�
		*/
		auto final_suspend() noexcept {
			std::cout << "Finished the coroutine" << std::endl;
			return std::suspend_always{};
		}

		/*
			���Э�̷����쳣�Ĵ���
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
		ʵ���ϵ�һ��������һ��Э���ǣ���������Ϊ�������������¶���:

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
	
	��������һ��Э���������ص����ӣ�

	һ��������(function body)�к���c++20�����������Ĺؼ���(co_return, co_yield, co_await)֮һ����ô�����������һ��Э��.
	Ȼ��������涨: co_return�ķ��ض��������Ҫ��promise_type���ͺ�����API��������������:
	struct promise_type {
		  sync<int> get_return_object() { return {}; }
		  std::suspend_never initial_suspend() { return {}; }
		  std::suspend_never final_suspend() noexcept { return {}; }
		  void return_void() {} //ע:return_void��return_value����ֻ�������һ��
		  void return_value(int val) {
			  //save coroutine return value
		  }
		  void unhandled_exception() { std::terminate(); }
	  ��

	  C++20��Э�����Ե�����ԭ��������û��Ĵ���Ҫ�ͱ�����һ����ϲ������һ��Э��
	  һЩ��Ҫ�ĺ������Ѿ�������������������ע��

	  �����Э��ִ����󣬴�ӡ�Ľ����

		1: Promise created		��Э��֡�ﴴ��һ��promise����,������������Э��֡
		2: Construct a sync object		����һ��Э�̺�caller��ͨ�Ŷ��󷵻ظ�caller
		3: Started the coroutine	����ִ�л����ں���ִ��(�����������)������(coroutine body)
		4: Execute the coroutine function body		ִ�к�����(coroutine body)
		5: Got coroutine result 52		�õ�Э�̵ķ���ֵ
		6: Finished the coroutine		Э���Ѿ�ִ������
		7: Created a coroutine			�ص�caller����һ�д���
		8: We got the return value...	called��ȡЭ�̵ķ���ֵ
		9: The coroutine result: 52		�õ�����ֵ
		10: Destruct a sync object		����sync����
		11: Promise died				��sync����������ݻ�promise����(��Ϊ���������final_suspend���ص���suspend_always, ���Э�̲����Զ�����)
	*/
	auto coro = my_coroutine1();
	std::cout << "Created a coroutine" << std::endl;
	auto result = coro.get();
	std::cout << "The coroutine result: " << result << std::endl;

	std::cout << "----testCoroutineWithNoDalay End -----" << std::endl;
}