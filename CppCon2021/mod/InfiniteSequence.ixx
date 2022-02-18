module;

#include <algorithm>  // generate_n
#include <iostream>  // cout
#include <iterator>  // ostream_iterator
#include <ranges>  // take
#include <utility>  // exchange

export module InfiniteSequence;

import InfiniteSequenceGenerator;
import InfiniteSequenceCoroutine;

// Raw for loop
void using_raw_for_loop(int first, int step, size_t num_steps)
{
    std::cout << "Using raw for loop: ";
    int current{ first };
    for (size_t i{ 0 }; i < num_steps; ++i)
    {
        std::cout << std::exchange(current, current + step) << " ";
    }
    std::cout << "\n";
}

// STL algorithm
void using_stl_algorithm(int first, int step, size_t num_steps)
{
    std::cout << "Using STL algorithm: ";
    std::generate_n(std::ostream_iterator<int>(std::cout, " "), num_steps,
        [current=first, &step]() mutable { return std::exchange(current, current + step); });
    std::cout << "\n";
}

// Function object
void using_function_object(int first, int step, size_t num_steps)
{
    std::cout << "Using function object: ";
    if (num_steps == 0) { return; }
    InfiniteSequenceGenerator seq(first, step);
    for (size_t i{ 0 }; i < num_steps; ++i)
    {
        std::cout << seq() << " ";
    }
    std::cout << "\n";
}

// Coroutine
void using_coroutine(int first, int step, size_t num_steps)
{
    std::cout << "Using coroutine: ";
    if (num_steps == 0) { return; }
    size_t i{ 0 };
    for (auto n : infinite_sequence_coroutine(first, step))
    {
        if (i++ < num_steps) { std::cout << n << " "; }
        else { break; }
    }
    std::cout << "\n";
}

// Coroutine, ranges, and raw for loop
void using_coroutine_ranges_raw_for_loop(int first, int step, size_t num_steps)
{
    std::cout << "Using coroutine, ranges, and raw for loop: ";
    if (num_steps == 0) { return; }
    for (auto n : infinite_sequence_coroutine(first, step) | std::ranges::views::take(num_steps))
    {
        std::cout << n << " ";
    }
    std::cout << "\n";
}

// Coroutine, ranges, STL algorithm
void using_coroutine_ranges_stl_algorithm(int first, int step, size_t num_steps)
{
    std::cout << "Using coroutine, ranges, STL algorithm: ";
    std::ranges::copy(infinite_sequence_coroutine(first, step) | std::ranges::views::take(num_steps),
        std::ostream_iterator<int>(std::cout, " "));
    std::cout << "\n";
}

export void infinite_sequence_main()
{
    // Raw for loop
    using_raw_for_loop(0, -5, 10);

    // STL algorithm
    using_stl_algorithm(0, -5, 10);

    // Function object
    using_function_object(0, -5, 10);

    // Coroutine
    using_coroutine(0, -5, 10);

    // Coroutine, ranges, and raw for loop
    using_coroutine_ranges_raw_for_loop(0, -5, 10);

    // Coroutine, ranges, STL algorithm
    using_coroutine_ranges_stl_algorithm(0, -5, 10);
}
