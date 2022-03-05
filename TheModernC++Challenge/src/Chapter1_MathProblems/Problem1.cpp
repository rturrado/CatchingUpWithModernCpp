#include "Chapter1_MathProblems.h"
#include "RtcConsoleRead.h"  // read_positive_number
#include "RtcPrint.h"

#include <iostream>  // cout
#include <vector>

// Sum of naturals divisible by 3 and 5
// Write a program that calculates and prints the sum of all natural numbers divisible by either 3 or 5,
// up to a given limit entered by the user
void problem_1_main()
{
    // Read limit
    auto n{ read_positive_number("Please enter a number (starting from 0): ", 0) };

    // Calculate the sum
    auto sum{ 0ull };
    std::vector<size_t> v{};
    for (auto i = 0u; i <= n; ++i)
    {
        if ((i % 3 == 0) || (i % 5 == 0))
        {
            sum += i;
            v.push_back(i);
        }
    }
    std::cout << "The sum of all natural numbers divisible by either 3 or 5 and up to " << n
        << " is:\n\t" << sum << " " << v << "\n\n";
}
