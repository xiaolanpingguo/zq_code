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

	// 下面这个代码在这个例子中没有用到
	// 不过这说明了如果awaitable有co_await操作符，就调用它的co_await操作符来返回awaiter；
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

	// 用于恢复之前等待异步读而挂起的协程，从而获得awaiter的返回值。
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

	// 调用co_await的进入的第一个函数，
	// true: 不会挂起协程，直接返回到co_wait的下一行代码
	// false: 挂起协程，接下里会调用await_suspend
	bool await_ready() const noexcept { return false; }

	// 开启一个线程去执行异步函数，目的是不会阻塞到caller
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

	// 当协程从恢复的时候，返回给co_await的值
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
		当编译器遇到co_await xxx(用户的表达式)，会增加下面伪代码
		{
		  auto&& value = xxx(用户的表达式);
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

		这个模板框架代码先获取表达式的值，然后根据它来获取awaitable, get_awaitable的伪代码:
		template<typename P, typename T>
		decltype(auto) get_awaitable(P& promise, T&& expr)
		{
		  if constexpr (has_any_await_transform_member_v<P>)
			return promise.await_transform(static_cast<T&&>(expr));
		  else
			return static_cast<T&&>(expr);
		}

		如果协程的promise中定义了await_transform，那么就调用await_transform来得到awaitable，否则就把自己作为awaitable返回,
		这里，我们没有在task里面定义await_transform，因此std::suspend_always将作为awaitable, 它的实现代码：

		在获取了awaitable对象std::suspend_always后，再根据它来获取awaiter，get_awaiter的伪代码：
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

		这个get_awaiter的返回值就是awaiter，它的实现有3个分支：
			如果awaitable有co_await操作符，就调用它的co_await操作符来返回awaiter；
			如果它没有co_await操作符就调用全局的co_await操作符，看看awaitable能否被全局的co_await调用，如果能调用就调用全局的co_await操作符来返回awaiter；
			如果都没有，那么就直接将awaitable作为awaiter返回出去

		而awaiter必须存在await_ready, await_suspend和await_resume三个函数，我们可以看到STL的suspend_always也有这3个API，
		这个三个API解释作用如下:
		如果awaiter.await_ready()返回false就挂起协程，接着调用awaiter.await_suspend，
			如果await_suspend返回void或者true，那就返回到caller，
			如果返回false就执行协程函数中co_await下面的语句；
		如果awaiter.await_ready()返回true说明协程已经执行完了，这时候调用awaiter.await_resume返回协程的结果。
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
	
	该例子将介绍co_await

	co_await操作符在概念上和函数调用符是类似的，当一个对象有函数调用符就认为它是一个函数对象即callable，
	当某个对象“支持”co_wait操作符时，那么它就是一个awaitable，是不是和callable的概念是类似的.

	为什么需要协程，就是在很多情况下，我们需要用同步的代码写法来获取一个异步事件的结果，那要怎么做到呢。
	关键就是异步的那个协程在执行完成后，需要通知我们，为此我们可以创建一个等待的协程，这个协程和caller之间通过一个事件来通信，caller那里阻塞等待事件，
	等待协程执行的时候也是被等待协程完成的时候通过事件通知caller被等待的协程已经完成了，
	具体可以在awaiter上做文章，在协程创建后挂起，把协程句柄传入到被等待的协程中，被等待协程执行完成之后恢复等待协程，等待协程给阻塞的caller发完成通知。

	这里我们通过std::promise来实现协程和caller之间的通信，当然这里你也可以换成条件变量或者等待事件之类的东西。
	先创建了一个SyncWaitTask协程，这个协程唯一的目的就是给caller发通知表示等待结束。
	这个SyncWaitTask协程是在被等待协程的final_suspend里恢复的，因为fina_suspend是在协程函数体执行之后调用的，
	所以在final_suspend里就说明协程已经执行完了，在这里恢复SyncWaitTask是最好的

	*/

	auto time1 = std::chrono::system_clock::now();

	auto lazy_read_task = readFile();
	auto read_size = SyncWait(std::move(lazy_read_task));

	auto time2 = std::chrono::system_clock::now();

	std::cout << "time cost:" << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::nanoseconds(time2 - time1)).count() << std::endl;

	std::cout << "----testCoroutineAwait End -----" << std::endl;
}