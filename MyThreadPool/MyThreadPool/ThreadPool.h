#include <vector>
#include <future>
#include <thread>
#include <mutex>
#include <atomic>

#pragma once
class ThreadPool
{
	std::vector<std::thread> threads;

	void Work();

	std::mutex myMutext;

	std::vector<std::pair<std::function<int()>, std::promise<int>>> tasks;

public:
	ThreadPool();

	~ThreadPool();

	std::future<int> AddTask(std::function<int()>);

	inline static ThreadPool& GetInstace() {
		static ThreadPool pool;
		return pool;
	}

private:
	ThreadPool(const ThreadPool&) = delete;

	ThreadPool& operator= (const ThreadPool&) = delete;
};

