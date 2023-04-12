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
			ͨ���������caller����ͨ�ţ�Э�̵�Э��֡����std::coroutine_handle
		*/
		auto get_return_object() {
			return Lazy<T>{ std::coroutine_handle<promise_type>::from_promise(*this) };
		}

		/*
			�������std::suspend_never�ͱ�ʾ����ͣЭ�̣������ִ��Э�̺�����(coroutine body)��
			������ص���std::suspend_always�ͱ�ʾ����Э�̺���ͣ��������ȥִ��coroutine body�������ִ�з��ص�caller���
		*/
		auto initial_suspend() {
			std::cout << "Started the coroutine" << std::endl;
			return std::suspend_always{};
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

Lazy<int> my_coroutine()
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

void testCoroutineWithLazy()
{
	std::cout << "----testCoroutineWithLazy Begin -----" << std::endl;
	/*
	
	�ڵ�һ�������У�Э����һ���������ص�Э�̣����Ǵ󲿷���������Ƕ���Ҫ�Լ�ȥ����Э�̵���ͣ�ͻָ���
	��Ȼ���ǻ���Э�̸�ʲô��

	��������������У�����ʵ��һ�������Լ����Ƶ�һ��Э�̣����ǰ�Э�̿�ʼ�ͽ�����״̬�����ó�suspend_always��
	Ȼ����caller����get()��ʱ�����ǻָ�Э��

	  �����Э��ִ����󣬴�ӡ�Ľ��:
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