#include "Chapter1_MathProblems.h"
#include "Digits.h"
#include "Utils.h"

#include <cmath>
#include <iostream>

// Armstrong numbers

// Write a program that prints all Armstrong numbers with three digits
void print_armstrong_numbers_with_three_digits()
{
    std::cout << "Armstrong numbers with three digits:\n";
    for (int i = 1; i <= 9; ++i)
    {
        for (int j = 0; j <= 9; ++j)
        {
            for (int k = 0; k <= 9; ++k)
            {
                int n = i * 100 + j * 10 + k;
                if (n == i * i * i + j * j * j + k * k * k)
                {
                    std::cout << "\t" << n << "\n";
                }
            }
        }
    }
}

// Write a function that determines the Armstrong numbers up to a limit, regardless of their number of digits
// v1: using a std::string for converting a number to a container of digits
void print_armstrong_numbers_up_to_a_limit_v1(size_t n, bool printResults)
{
    // Print Armstrong numbers
    if (printResults) std::cout << "Armstrong numbers up to " << n << ":\n";
    for (auto i = 0u; i <= n; ++i)
    {
        // Turn current number into a string
        std::string digits{ std::to_string(i) };

        auto sum_of_powers = std::accumulate(digits.cbegin(), digits.cend(), static_cast<size_t>(0),
            [digits_size = digits.size()](size_t total, size_t digit) {
                return total + static_cast<size_t>(std::pow(digit - '0', digits_size));
            });
        if (i == sum_of_powers)
        {
            if (printResults) std::cout << "\t" << i << "\n";
        }
    }
}

// Write a function that determines the Armstrong numbers up to a limit, regardless of their number of digits
// v2: using Digits class for converting a number to a container of digits
void print_armstrong_numbers_up_to_a_limit_v2(size_t n, bool printResults)
{
    // Turn current number into a deque of numbers
    Digits<size_t> digits{};

    // Print Armstrong numbers
    if (printResults) std::cout << "Armstrong numbers up to " << n << ":\n";
    for (auto i = 0u; i <= n; ++i, ++digits)
    {
        auto sum_of_powers = std::accumulate(digits.cbegin(), digits.cend(), static_cast<size_t>(0),
            [digits_size = digits.size()](size_t total, size_t digit) {
                return total + static_cast<size_t>(std::pow(digit, digits_size));
            });
        if (i == sum_of_powers)
        {
            if (printResults) std::cout << "\t" << i << "\n";
        }
    }
}

// Write a function that determines the Armstrong numbers up to a limit, regardless of their number of digits
// v3: book's version
void print_armstrong_numbers_up_to_a_limit_v3(int const n, bool printResults)
{
    if (printResults) std::cout << "Armstrong numbers up to " << n << ":\n";
    for (int i = 0; i <= n; ++i)
    {
        std::vector<int> digits;
        int n = i;
        while (n > 0)
        {
            digits.push_back(n % 10);
            n = n / 10;
        }

        int arm = std::accumulate(
            std::begin(digits), std::end(digits),
            0,
            [s = digits.size()](int const sum, int const digit) {return sum + static_cast<int>(std::pow(digit, s)); });

        if (i == arm)
        {
            if (printResults) std::cout << "\t" << arm << "\n";
        }
    }
}

void problem_8_main()
{
    print_armstrong_numbers_with_three_digits();

    // Read limit
    auto n{ read_positive_number(0) };
    // Print Armstrong numbers up to the limit
    print_armstrong_numbers_up_to_a_limit_v1(n, true);
    print_armstrong_numbers_up_to_a_limit_v2(n, true);

    auto t1 = perf_timer<>::duration([]() { for (int i = 0; i < 10000; ++i) print_armstrong_numbers_up_to_a_limit_v1(1000, false); });
    std::cout << std::chrono::duration<double, std::milli>(t1).count() << "ms" << std::endl;

    auto t2 = perf_timer<>::duration([]() { for (int i = 0; i < 10000; ++i) print_armstrong_numbers_up_to_a_limit_v2(1000, false); });
    std::cout << std::chrono::duration<double, std::milli>(t2).count() << "ms" << std::endl;

    auto t3 = perf_timer<>::duration([]() { for (int i = 0; i < 10000; ++i) print_armstrong_numbers_up_to_a_limit_v3(1000, false); });
    std::cout << std::chrono::duration<double, std::milli>(t3).count() << "ms" << std::endl;
}
