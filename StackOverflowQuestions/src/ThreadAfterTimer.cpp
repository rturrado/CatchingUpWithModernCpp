#include <chrono>
#include <iostream>  // cout
#include <future>  // async
#include <thread>  // sleep_for

void thread_after_timer_main()
{
    using namespace std::chrono_literals;
    auto f1 = std::async(std::launch::async, []() {
        for (int i{ 0 }; i < 10; ++i)
        {
            std::this_thread::sleep_for(1s);
            std::cout << ".";
        }
    });
    auto f2 = std::async(std::launch::async, []() {
        std::this_thread::sleep_for(5s);
        std::cout << "Hello, world!";
    });
    f1.wait();
    f2.wait();
}
