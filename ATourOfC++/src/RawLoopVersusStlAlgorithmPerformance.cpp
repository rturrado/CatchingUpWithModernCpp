#include <algorithm>
#include <chrono>
#include <iostream>
#include <limits>
#include <random>
#include <vector>

#include "RawLoopVersusStlAlgorithmPerformance.h"

// You have to compile in Release (and with optimizations) to see that the STL algorithm is faster than the for raw loop
// Otherwise, the lambda used by the STL algorithm is compiled as a function and is called for every vector element

void benchmark(std::vector<int>& input, size_t size)
{
    auto start = std::chrono::high_resolution_clock::now();
    size_t bigger_than_21_count = 0;
    for (auto& n : input)
    {
        if (n > 21)
        {
            bigger_than_21_count++;
        }
    }
    auto end = std::chrono::high_resolution_clock::now();

    using fms = std::chrono::duration<long double, std::chrono::milliseconds::period>;
    auto interval = fms(end - start);
    std::cout << "1) Raw loop: " << std::fixed << fms(interval).count() << "ms\n";

    start = std::chrono::high_resolution_clock::now();
    bigger_than_21_count = std::count_if(input.begin(), input.end(), [](const auto& n) { return (n > 21); });
    end = std::chrono::high_resolution_clock::now();

    interval = fms(end - start);
    std::cout << "2) STL algorithm: " << std::fixed << fms(interval).count() << "ms\n";
}

void raw_loop_versus_stl_algorithm_performance_main()
{
    const std::vector<size_t> vector_sizes = { 100'000, 1'000'000, 10'000'000 };

    for (const auto& size : vector_sizes)
    {
        std::cout << "Benchmarking: vector size = " << size << "\n";

        std::vector<int> input(size, 0);
        // Fill input with numbers in the range [1, 100]
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_int_distribution<int> dist(1, 100);
        std::for_each(input.begin(), input.end(), [&dist, &mt](int &n) { n = dist(mt); });

        benchmark(input, size);
        std::cout << "\n";
    }
}
