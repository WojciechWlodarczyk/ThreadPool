#include <iostream>
#include <future>
#include <thread>
#include "ThreadPool.h"

int main()
{
    auto result = ThreadPool::GetInstace().AddTask([]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        std::printf("Thread wykonal!");
        return 1;
        });
    std::cout << "result " << result.get();

    std::cout << "Hello World!\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));

}