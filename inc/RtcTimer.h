#ifndef RTC_TIMER_H
#define RTC_TIMER_H

#include <chrono>  // high_resolution_clock, microseconds
#include <functional>  // invoke
#include <utility>  // forward

template <typename Time = std::chrono::microseconds, typename Clock = std::chrono::high_resolution_clock>
struct function_timer
{
    template <typename F, typename... Args>
    static Time duration(F&& f, Args... args)
    {
        auto start = Clock::now();

        std::invoke(std::forward<F>(f), std::forward<Args>(args)...);

        auto end = Clock::now();

        return std::chrono::duration_cast<Time>(end - start);
    }
};

#endif  // RTC_TIMER_H
