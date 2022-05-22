#include "ThreadPool.h"
#include <vector>
#include <future>
#include <thread>
#include <mutex>
#include <atomic>

ThreadPool::ThreadPool()
{
	for (int i = 0; i < std::thread::hardware_concurrency(); i++)
	{
		threads.push_back(std::thread{ &ThreadPool::Work, this });
	}
}

ThreadPool::~ThreadPool()
{
	for (auto& thread  : threads)
	{
		if(thread.joinable())
			thread.join();
	}
}

std::future<int> ThreadPool::AddTask(std::function<int()> task)
{
	std::lock_guard<std::mutex> lg(myMutext);
	std::promise<int> myPromise;
	std::future<int> myFuture = myPromise.get_future();
	auto newPair = std::make_pair(task, std::move(myPromise));
	tasks.push_back(std::move(newPair));
	return myFuture;
}

void ThreadPool::Work() {
	while (true)
	{
		std::function<int()> nextTask;
		std::promise<int> prom;
		{
			std::lock_guard<std::mutex> lg(myMutext);

			if (tasks.empty())
				return;

			nextTask = tasks[0].first;
			prom = std::move(tasks[0].second);
			tasks.erase(tasks.begin());
		}
		prom.set_value(nextTask());
	}
}