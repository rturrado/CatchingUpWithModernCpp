#include "Chapter1_MathProblems.h"
#include "Chapter1_MathProblems/Math.h"  // is_prime
#include "RtcConsoleRead.h"  // read_positive_number

#include <iostream>  // cout

size_t biggest_prime_smaller_than(const size_t n)
{
    return (is_prime(n - 1) ? n - 1 : biggest_prime_smaller_than(n - 1));
};

// Largest prime smaller than given number
// Write a program that computes and prints the largest prime number
// that is smaller than a number provided by the user, which must be a positive integer
void problem_4_main()
{
    // Read limit
    auto limit{ read_positive_number("Please enter a number (starting from 2): ", 2) };

    // Calculate biggest prime smaller than limit
    std::cout << "Biggest prime number smaller than " << limit << " is: " << biggest_prime_smaller_than(limit) << "\n\n";
}
