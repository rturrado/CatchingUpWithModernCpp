#include "Chapter1_MathProblems.h"
#include "Chapter1_MathProblems/Math.h"  // divisors
#include "RtcConsoleRead.h"  // read_positive_number
#include "RtcPrint.h"

#include <iostream>  // cout
#include <numeric>  // accumulate


// Abundant numbers
// Write a program that prints all abundant numbers and their abundance, up to a number entered by the user
void problem_6_main()
{
    // Read limit
    auto limit{ read_positive_number(1) };

    // Print abundant numbers up to the limit and their abundance
    std::cout << "Abudant numbers up to " << limit << ", {list of divisors}, (and their abundance):\n";
    for (auto i = 1u; i <= limit; ++i)
    {
        auto d = divisors(i);
        auto sum = std::accumulate(d.cbegin(), d.cend(), 0u);
        if (sum > i)
        {
            std::cout << "\t"<< i << " " << d << " (" << sum - i << ")\n";
        }
    }
    std::cout << "\n";
}
