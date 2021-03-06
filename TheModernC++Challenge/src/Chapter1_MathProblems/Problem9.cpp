#include "Chapter1_MathProblems.h"
#include "Chapter1_MathProblems/Math.h"  // prime_factors
#include "RtcConsoleRead.h"  // read_positive_number
#include "RtcPrint.h"

#include <iostream>  // cout

// Prime factors of a number
// Write a program that prints the prime factors of a number entered by the user
void problem_9_main()
{
    // Read a positive number
    auto n{ read_positive_number("Please enter a number (starting from 0): ", 0) };

    // Print the prime factors of that number
    std::cout << "The prime factors of " << n << " are: " << prime_factors(n) << "\n\n";
}
