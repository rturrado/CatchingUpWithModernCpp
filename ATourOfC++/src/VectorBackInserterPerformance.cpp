#include <algorithm>
#include <chrono>
#include <iostream>
#include <vector>

#include "VectorBackInserterPerformance.h"

void benchmark(size_t size)
{
    std::vector<int> input(size, 0);

    auto start = std::chrono::high_resolution_clock::now();
    std::vector<int> output1(input.size(), 0);  // 1) We initialize a vector with a given size
    std::transform(input.begin(), input.end(), output1.begin(),  // Then use transform directly on it
        [](const auto& n) { return n * 3; });
    auto end = std::chrono::high_resolution_clock::now();

    using fms = std::chrono::duration<long double, std::chrono::milliseconds::period>;
    auto interval = fms(end - start);
    std::cout << "1) Initializing vector with a given size: " << std::fixed << fms(interval).count() << "ms\n";

    start = std::chrono::high_resolution_clock::now();
    std::vector<int> output2;  // 2) We define a vector without initializing it
    std::transform(input.begin(), input.end(), back_inserter(output2),  // Then use transform appending every new element to the end of it
        [](const auto& n) { return n * 3; });
    end = std::chrono::high_resolution_clock::now();

    interval = fms(end - start);
    std::cout << "2) Using back inserter: " << std::fixed << fms(interval).count() << "ms\n";
}

void vector_back_inserter_performance_main()
{
    const std::vector<size_t> vector_sizes = { 100'000, 1'000'000, 10'000'000 };

    for (const auto& size : vector_sizes)
    {
        std::cout << "Benchmarking: vector size = " << size << "\n";
        benchmark(size);
        std::cout << "\n";
    }
}
