#include <coroutine>
#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <filesystem>
#include <variant>
#include <fstream>
#include <future>


template<typename T>
struct Promise;

template<typename T>
struct Task {

private:
	Task(Promise<T>* promise) : m_promise{promise }
	{

	}
	Promise<T>* m_promise = nullptr;

	template<typename>
	friend struct Promise;

public:
	using promise_type = Promise<T>;
	Task() = default;

	// ����������������������û���õ�
	// ������˵�������awaitable��co_await���������͵�������co_await������������awaiter��
	auto operator co_await() const noexcept {
		struct Awaiter {
			bool await_ready() const noexcept {
				return promise.isReady();
			}

			using CoroHandle = std::coroutine_handle<>;
			CoroHandle await_suspend(CoroHandle continuation) const noexcept {
				promise.continuation = continuation;
				return std::coroutine_handle<Promise<T>>::from_promise(promise);
			}

			T&& await_resume() const {
				return promise.getResult();
			}

			Promise<T>& promise;
		};
		return Awaiter{ *m_promise };
	}

	auto get_handle() { return m_promise->get_handle(); }

	void set_continue(std::coroutine_handle<> h) {

		//auto h1 = std::coroutine_handle<>::from_promise(m_promise);
		//auto p1 = h.promise();
		m_promise->continuation = h;
	}

	T&& getResult() {
		return m_promise->getResult();
	}
};

template<typename T>
struct Promise {
	auto get_return_object() {
		return Task<T>{this};
	}
	std::suspend_never initial_suspend() noexcept { return {}; }

	// ���ڻָ�֮ǰ�ȴ��첽���������Э�̣��Ӷ����awaiter�ķ���ֵ��
	auto final_suspend() noexcept {
		struct FinalAwaiter {
			bool await_ready() const noexcept { return false; }
			void await_suspend(std::coroutine_handle<Promise<T>> thisCoro) noexcept {
				auto& promise = thisCoro.promise();
				if (promise.continuation)
					promise.continuation();
			}
			void await_resume() const noexcept {}
		};

		return FinalAwaiter{};
	}
	void unhandled_exception() { std::terminate(); }

	template<typename U>
	void return_value(U&& value)
	{
		result.template emplace<1>(std::forward<U>(value));
	}

	T&& getResult() {
		if (result.index() == 2)
			std::rethrow_exception(std::get<2>(result));
		return std::move(std::get<1>(result));
	}

	bool isReady() {
		return result.index() != 0;
	}

	std::variant<std::monostate, T, std::exception_ptr> result;
	std::coroutine_handle<> continuation;
};

struct SyncWaitTask {
	struct promise_type {
		auto get_return_object() {
			return SyncWaitTask{ std::coroutine_handle<promise_type>::from_promise(*this) };
		}
		auto initial_suspend() {
			return std::suspend_always{};
		}
		void return_void() {
		}
		auto final_suspend() noexcept {
			return std::suspend_never{};
		}
		void unhandled_exception() {
			std::exit(1);
		}
	};

	auto get_handle() {
		return handle_;
	}

	std::coroutine_handle<promise_type> handle_;
};


template<class T>
auto SyncWait(T task) {
	std::promise<void> promise;
	auto helper = [&]()->SyncWaitTask {
		promise.set_value();
		co_return;
	};

	SyncWaitTask helper_task = helper();

	task.set_continue(helper_task.get_handle());
	promise.get_future().wait();
	return task.getResult();
}


struct AsyncReadFile {
	AsyncReadFile(std::filesystem::path path) : path{ std::move(path) } {}

	// ����co_await�Ľ���ĵ�һ��������
	// true: �������Э�̣�ֱ�ӷ��ص�co_wait����һ�д���
	// false: ����Э�̣�����������await_suspend
	bool await_ready() const noexcept { return false; }

	// ����һ���߳�ȥִ���첽������Ŀ���ǲ���������caller
	void await_suspend(std::coroutine_handle<> coro) {
		auto work = [this, coro]() mutable {
			std::cout << std::this_thread::get_id() << " worker thread: opening file\n";
			auto stream = std::ifstream{ path, std::ios::in | std::ios::binary };
			if (stream.is_open())
			{
				char buff[1024 * 256] = {};
				stream.seekg(0, std::ios::end);
				auto filesize = stream.tellg();

				stream.seekg(0, std::ios::beg);
				stream.read(buff, filesize);
				stream.close();

				std::cout << std::this_thread::get_id() << "file read compelete, file size: " << filesize << "\n";

				result.assign(buff, filesize);
				coro();

				std::cout << std::this_thread::get_id() << " worker thread: exiting\n";
			}
			else
			{
				coro();
			}
		};
		std::thread{ work }.detach();
	}

	// ��Э�̴ӻָ���ʱ�򣬷��ظ�co_await��ֵ
	std::string await_resume() noexcept {
		return std::move(result);
	}

private:
	std::filesystem::path path;
	std::string result;
};


Task<size_t> readFile()
{
	/*
		������������co_await xxx(�û��ı��ʽ)������������α����
		{
		  auto&& value = xxx(�û��ı��ʽ);
		  auto&& awaitable = get_awaitable(promise, static_cast<decltype(value)>(value));
		  auto&& awaiter = get_awaiter(static_cast<decltype(awaitable)>(awaitable));
		  if (!awaiter.await_ready())
		  {
			using handle_t = std::experimental::coroutine_handle<P>;

			using await_suspend_result_t =
			  decltype(awaiter.await_suspend(handle_t::from_promise(p)));

			<suspend-coroutine>

			if constexpr (std::is_void_v<await_suspend_result_t>)
			{
			  awaiter.await_suspend(handle_t::from_promise(p));
			  <return-to-caller-or-resumer>
			}
			else
			{
			  static_assert(
				 std::is_same_v<await_suspend_result_t, bool>,
				 "await_suspend() must return 'void' or 'bool'.");

			  if (awaiter.await_suspend(handle_t::from_promise(p)))
			  {
				<return-to-caller-or-resumer>
			  }
			}

			<resume-point>
		  }

		  return awaiter.await_resume();
		}

		���ģ���ܴ����Ȼ�ȡ���ʽ��ֵ��Ȼ�����������ȡawaitable, get_awaitable��α����:
		template<typename P, typename T>
		decltype(auto) get_awaitable(P& promise, T&& expr)
		{
		  if constexpr (has_any_await_transform_member_v<P>)
			return promise.await_transform(static_cast<T&&>(expr));
		  else
			return static_cast<T&&>(expr);
		}

		���Э�̵�promise�ж�����await_transform����ô�͵���await_transform���õ�awaitable������Ͱ��Լ���Ϊawaitable����,
		�������û����task���涨��await_transform�����std::suspend_always����Ϊawaitable, ����ʵ�ִ��룺

		�ڻ�ȡ��awaitable����std::suspend_always���ٸ���������ȡawaiter��get_awaiter��α���룺
		template<typename Awaitable>
		decltype(auto) get_awaiter(Awaitable&& awaitable)
		{
		  if constexpr (has_member_operator_co_await_v<Awaitable>)
			return static_cast<Awaitable&&>(awaitable).operator co_await();
		  else if constexpr (has_non_member_operator_co_await_v<Awaitable&&>)
			return operator co_await(static_cast<Awaitable&&>(awaitable));
		  else
			return static_cast<Awaitable&&>(awaitable);
		}

		���get_awaiter�ķ���ֵ����awaiter������ʵ����3����֧��
			���awaitable��co_await���������͵�������co_await������������awaiter��
			�����û��co_await�������͵���ȫ�ֵ�co_await������������awaitable�ܷ�ȫ�ֵ�co_await���ã�����ܵ��þ͵���ȫ�ֵ�co_await������������awaiter��
			�����û�У���ô��ֱ�ӽ�awaitable��Ϊawaiter���س�ȥ

		��awaiter�������await_ready, await_suspend��await_resume�������������ǿ��Կ���STL��suspend_alwaysҲ����3��API��
		�������API������������:
		���awaiter.await_ready()����false�͹���Э�̣����ŵ���awaiter.await_suspend��
			���await_suspend����void����true���Ǿͷ��ص�caller��
			�������false��ִ��Э�̺�����co_await�������䣻
		���awaiter.await_ready()����true˵��Э���Ѿ�ִ�����ˣ���ʱ�����awaiter.await_resume����Э�̵Ľ����
	*/

	std::cout << std::this_thread::get_id() << " readFile(): about to read file async\n";
	const auto result = co_await AsyncReadFile{ "E:\\cache\\googledownload\\ch_cn.zip" };
	std::cout << std::this_thread::get_id() << " readFile(): about to return (size " << result.size() << ")\n";

	co_return result.size();
}

void testCoroutineAwait()
{
	std::cout << "----testCoroutineAwait Begin -----" << std::endl;
	/*
	
	�����ӽ�����co_await

	co_await�������ڸ����Ϻͺ������÷������Ƶģ���һ�������к������÷�����Ϊ����һ����������callable��
	��ĳ������֧�֡�co_wait������ʱ����ô������һ��awaitable���ǲ��Ǻ�callable�ĸ��������Ƶ�.

	Ϊʲô��ҪЭ�̣������ںܶ�����£�������Ҫ��ͬ���Ĵ���д������ȡһ���첽�¼��Ľ������Ҫ��ô�����ء�
	�ؼ������첽���Ǹ�Э����ִ����ɺ���Ҫ֪ͨ���ǣ�Ϊ�����ǿ��Դ���һ���ȴ���Э�̣����Э�̺�caller֮��ͨ��һ���¼���ͨ�ţ�caller���������ȴ��¼���
	�ȴ�Э��ִ�е�ʱ��Ҳ�Ǳ��ȴ�Э����ɵ�ʱ��ͨ���¼�֪ͨcaller���ȴ���Э���Ѿ�����ˣ�
	���������awaiter�������£���Э�̴�������𣬰�Э�̾�����뵽���ȴ���Э���У����ȴ�Э��ִ�����֮��ָ��ȴ�Э�̣��ȴ�Э�̸�������caller�����֪ͨ��

	��������ͨ��std::promise��ʵ��Э�̺�caller֮���ͨ�ţ���Ȼ������Ҳ���Ի��������������ߵȴ��¼�֮��Ķ�����
	�ȴ�����һ��SyncWaitTaskЭ�̣����Э��Ψһ��Ŀ�ľ��Ǹ�caller��֪ͨ��ʾ�ȴ�������
	���SyncWaitTaskЭ�����ڱ��ȴ�Э�̵�final_suspend��ָ��ģ���Ϊfina_suspend����Э�̺�����ִ��֮����õģ�
	������final_suspend���˵��Э���Ѿ�ִ�����ˣ�������ָ�SyncWaitTask����õ�

	*/

	auto time1 = std::chrono::system_clock::now();

	auto lazy_read_task = readFile();
	auto read_size = SyncWait(std::move(lazy_read_task));

	auto time2 = std::chrono::system_clock::now();

	std::cout << "time cost:" << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::nanoseconds(time2 - time1)).count() << std::endl;

	std::cout << "----testCoroutineAwait End -----" << std::endl;
}