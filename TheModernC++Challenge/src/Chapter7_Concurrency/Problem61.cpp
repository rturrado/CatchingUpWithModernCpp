#include "Chapter7_Concurrency.h"
#include "Timer.h"

#include <algorithm>  // max, min, transform
#include <cassert>  // assert
#include <execution>  // par
#include <format>
#include <future>  // async
#include <iostream>  // cout
#include <numeric>  // iota
#include <vector>

template <typename InputIt, typename OutputIt, typename UnaryOperation>
void parallel_transform(InputIt first, InputIt last, OutputIt d_first, UnaryOperation&& f)
{
    size_t size{ static_cast<size_t>(std::distance(first, last)) };
    
    const size_t THREAD_POOL_SIZE_MAX{ 4 };
    const size_t BLOCK_SIZE_MIN{ 100 };

    size_t thread_pool_size{ std::max(std::min(size / BLOCK_SIZE_MIN, static_cast<size_t>(1)), static_cast<size_t>(4)) };
    size_t block_size{ size / thread_pool_size };

    auto futures{ std::vector<std::future<void>>(thread_pool_size) };

    for (size_t i{ 0 }; i < thread_pool_size; ++i)
    {
        futures[i] = std::async(
            std::launch::async,
            [first, d_first, i, block_size, size, &f]() {
                std::transform(
                    first + i * block_size,
                    first + std::min(size, (i + 1) * block_size),
                    d_first + i * block_size,
                    std::forward<UnaryOperation>(f));
            }
        );
    }
    for (auto& ft: futures) { ft.get(); }
}

// Parallel transform algorithm
//
// Write a general-purpose algorithm that applies a given unary function to transform the elements of a range in parallel.
// The unary operation used to transform the range must not invalidate range iterators or modify the elements of the range.
// The level of parallelism, that is, the number of execution threads and the way it is achieved, is an implementation detail.
void problem_61_main()
{
    auto square = [](int n) { return n * n; };
    
    std::vector<int> v(10'000'000);
    std::iota(std::begin(v), std::end(v), 0);
    auto w{ v };
    auto x{ v };

    auto t1{ function_timer<>::duration(
        [&v, &square]() mutable {
            parallel_transform(std::cbegin(v), std::cend(v), std::begin(v), square);
        }
    ) };
    auto t2{ function_timer<>::duration(
        [&w, &square]() mutable {
            std::transform(std::cbegin(w), std::cend(w), std::begin(w), square);
        }
    ) };
    auto t3{ function_timer<>::duration(
        [&x, &square]() mutable {
            std::transform(std::execution::par, std::cbegin(x), std::cend(x), std::begin(x), square);
        }
    ) };

    assert("Error: vectors are different" and v == w);

    std::cout << std::format("Times:\n\tparallel_transform: {}\n\tstd::transform: {}\n\tstd::transform(ex::par): {}\n", t1, t2, t3);

    std::cout << "\n";
}
