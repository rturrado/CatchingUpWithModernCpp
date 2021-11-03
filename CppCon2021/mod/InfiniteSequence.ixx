module;

#include <iostream>  // cout
#include <ranges>  // take
#include <utility>  // exchange

#include <tl/generator.hpp>

export module InfiniteSequence;

import InfiniteSequenceGenerator;
import InfiniteSequenceCoroutine;

// For loop
void print_sequence_v1(int first, int step, size_t num_steps)
{
    if (num_steps == 0) { return; }
    std::cout << "v1: ";
    int current{ first };
    for (size_t i{ 0 }; i < num_steps; ++i)
    {
        std::cout << std::exchange(current, current + step) << " ";
    }
    std::cout << "\n";
}

// Function object
void print_sequence_v2(int first, int step, size_t num_steps)
{
    if (num_steps == 0) { return; }
    std::cout << "v2: ";
    InfiniteSequenceGenerator seq(0, -5);
    for (size_t i{ 0 }; i < num_steps; ++i)
    {
        std::cout << seq() << " ";
    }
    std::cout << "\n";
}

// Coroutine
void print_sequence_v3(int first, int step, size_t num_steps)
{
    if (num_steps == 0) { return; }
    std::cout << "v3: ";
    size_t i{ 0 };
    for (auto n : infinite_sequence_coroutine(first, step))
    {
        if (i++ < num_steps) { std::cout << n << " "; }
        else { break; }
    }
    std::cout << "\n";
}

// Coroutine plus ranges
void print_sequence_v4(int first, int step, size_t num_steps)
{
    if (num_steps == 0) { return; }
    std::cout << "v4: ";
    for (auto n : infinite_sequence_coroutine(first, step) | std::ranges::views::take(num_steps))
    {
        std::cout << n << " ";
    }
    std::cout << "\n";
}

// Coroutine plus ranges, no for loopvoid print_sequence_v5(int first, int step, size_t num_steps)
void print_sequence_v5(int first, int step, size_t num_steps)
{
    std::cout << "v5: ";
    std::ranges::copy(infinite_sequence_coroutine(first, step) | std::ranges::views::take(num_steps),
        std::ostream_iterator<int>(std::cout, " "));
    std::cout << "\n";
}

export void infinite_sequence_main()
{
    // For loop
    print_sequence_v1(0, -5, 10);

    // Function object
    print_sequence_v2(0, -5, 10);

    // Coroutine
    print_sequence_v3(0, -5, 10);

    // Coroutine plus ranges
    print_sequence_v4(0, -5, 10);

    // Coroutine plus ranges, no for loop
    print_sequence_v5(0, -5, 10);
}
