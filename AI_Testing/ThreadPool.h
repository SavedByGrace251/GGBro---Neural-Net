#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <condition_variable>
#include <functional>
#include <future>
#include <memory>
#include <mutex>
#include <queue>
#include <stdexcept>
#include <thread>
#include <vector>
using std::bind;
using std::condition_variable;
using std::future;
using std::function;
using std::forward;
using std::make_shared;
using std::mutex;
using std::packaged_task;
using std::queue;
using std::result_of;
using std::runtime_error;
using std::thread;
using std::unique_lock;
using std::vector;

/* Thread pooling class to aid in a more efficient use of threads */
class ThreadPool {
private:
	// need to keep track of threads so we can join them
	vector<thread> pool;

	// the task queue
	queue<function<void()>> tasks;

	// synchronization
	mutex queue_mutex;
	condition_variable condition;
	bool stop;

public:
	// initialize some amount of workers
	ThreadPool(size_t threads) : stop(false)
	{
		for (size_t i = 0; i < threads; ++i) {
			pool.emplace_back( [this]
			{
				while (true)
				{
					function<void()> task;
					{
						unique_lock<mutex> lock(this->queue_mutex);
						this->condition.wait(lock,
							[this] { return this->stop || !this->tasks.empty(); });
						if (this->stop && this->tasks.empty())
							return;
						task = move(this->tasks.front());
						this->tasks.pop();
					}
					task();
				}
			});
		}
	}

	// add new task to the pool
	template<class F, class... Args>
	void addTask(F&& f, Args&&... args)
	{
		using return_type = typename result_of<F(Args...)>::type;
		auto task = make_shared<packaged_task<return_type()>>(bind(forward<F>(f), forward<Args>(args)...));
		{
			unique_lock<mutex> lock(queue_mutex);
			// don't allow adding a task after stopping the pool
			if (stop)
				throw runtime_error("Adding task on stopped ThreadPool");
			tasks.emplace([task]() { (*task)(); });
		}
		condition.notify_one();
	}

	// join all threads in the pool on deconstruction
	~ThreadPool() {
		{
			unique_lock<mutex> lock(queue_mutex);
			stop = true;
		}
		condition.notify_all();
		for (thread &t : pool)
			t.join();
	}
};
#endif