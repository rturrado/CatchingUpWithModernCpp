#include "LogSystemWithCountingSemaphores.h"

#include <algorithm>  // for_each
#include <chrono>  // chrono_literasl
#include <future>  // async, future
#include <iostream>  // cout
#include <mutex>  // mutex, unique_lock
#include <queue>
#include <semaphore>  // counting_semaphore
#include <string>
#include <thread>  // sleep_for
#include <vector>

std::mutex mtx{};
std::queue<std::string> logs{};
std::counting_semaphore c_semaphore{ 0 };

void log_system_with_counting_semaphores_main()
{
    auto log = [](std::string message) {
        std::unique_lock lock{ mtx };
        logs.push(std::move(message));
        c_semaphore.release();
    };
    auto log_client = [&log]() {
        using namespace std::chrono_literals;
        static size_t s_id{ 1 };
        size_t id{ s_id++ };
        for (;;)
        {
            log(std::to_string(id));
            std::this_thread::sleep_for(id * 100ms);
        }
    };
    auto log_server = []() {
        for (;;)
        {
            c_semaphore.acquire();
            std::unique_lock lock{ mtx };
            std::cout << logs.front() << " ";
            logs.pop();
        }
    };

    std::vector<std::future<void>> log_clients(10);
    std::for_each(std::begin(log_clients), std::end(log_clients),
        [&log_client](auto& lc_fut) { lc_fut = std::async(std::launch::async, log_client); });
    auto ls_fut{ std::async(std::launch::async, log_server) };

    std::for_each(std::begin(log_clients), std::end(log_clients),
        [](auto& lc_fut) { lc_fut.wait(); });
    ls_fut.wait();
}
