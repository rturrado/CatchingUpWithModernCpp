// References: What's new in Visual Studio: 64-bit IDE, C++20, WSL 2, and more; Marian Luparu and Sy Brand; CppCon 2021

module;

#include <tl/generator.hpp>

export module InfiniteSequenceCoroutine;

export tl::generator<int> infinite_sequence_coroutine(int first, int step)
{
    int current{ first };
    while (true)
    {
        // tl::generator::promise::yield_value(int &) doesn't accept r-value references
        // co_yield std::exchange(current, current + step);
        co_yield current;
        current += step;
    }
}
