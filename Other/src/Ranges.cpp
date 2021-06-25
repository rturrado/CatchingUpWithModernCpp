#include <algorithm>
#include <iostream>
#include <numeric>
#include <ranges>
#include <vector>

void ranges_main()
{
    auto const ints = { 1, 2, 3, 5, 7, 11, 13, 17, 19 };
    auto even = [](int i) { return i % 2 == 0; };
    auto square = [](int i) { return i * i; };

    // Example 1: std::views, take, filter and transform
    std::cout << "Take the first prime numbers smaller than 20, "
        "filter out the odd values, "
        "then print the square of the even values: ";
    auto r1{ ints | std::views::take(5) | std::views::filter(even) | std::views::transform(square) };
    for (bool first{true}; auto&& i : r1)
    {
        std::cout << (first ? "" : " ") << i;
        first = false;
    }
    std::cout << "\n";

    // Example 2: generate_n, drop
    std::cout << "Generate a vector with the first 100 primes, "
        << "then drop the first 20, "
        << "and print the next 5: ";
    auto is_prime = [](int i)
    {
        if (i == 1 || i == 2)
        {
            return true;
        }
        if (i % 2 == 0)
        {
            return false;
        }
        for (auto j = 3; j < i; j += 2)
        {
            if (i % j == 0)
            {
                return false;
            }
        }
        return true;
    };
    auto next_prime = [&is_prime]() {
        static int i{ 0 };
        do
        {
            i++;
        }
        while (not is_prime(i));
        return i;
    };
    std::vector<int> v{};
    std::ranges::generate_n(std::back_inserter(v), 100, next_prime);
    auto r2{ v | std::views::drop(10) | std::views::take(5) };
    for (bool first{ true }; auto && i : r2)
    {
        std::cout << (first ? "" : " ") << i;
        first = false;
    }
    std::cout << "\n";

    // Example 3: accumulate working on a range
    std::cout << "Sum of previous vector: ";
    std::cout << std::accumulate(r2.begin(), r2.end(), 0);
}
