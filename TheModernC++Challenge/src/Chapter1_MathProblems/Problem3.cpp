#include "Chapter1_MathProblems.h"
#include "RtcConsoleRead.h"  // read_list_of_positive_numbers
#include "RtcPrint.h"

#include <algorithm>  // sort
#include <iostream>  // cout
#include <numeric>  // accumulate
#include <vector>

auto lcm(const std::vector<size_t>& v)
{
    auto biggest_number = v[v.size() - 1];
    auto possible_lcm{ biggest_number };
    for (size_t i = 1; ; ++i)
    {
        possible_lcm = biggest_number * i;

        auto accum_plus_possible_lcm_mod_n = [&possible_lcm](size_t accum, size_t n) {
            return accum + possible_lcm % n;
        };

        size_t sum_of_mods = std::accumulate(std::next(v.crbegin()), v.crend(), static_cast<size_t>(0), accum_plus_possible_lcm_mod_n);

        if (sum_of_mods == 0)
        {
            break;
        }
    }
    return possible_lcm;
};

// Least common multiple
// Write a program that will, given two or more positive integers, calculate and print the least common multiple of them all
void problem_3_main()
{
    // Read a list of positive numbers
    auto v{ read_list_of_positive_numbers(2, 0) };

    // Sort list
    std::sort(v.begin(), v.end());

    // Calculate the least common multiple
    //
    // I sort the input numbers, and take the biggest one
    // Then, I find the number that is 1, 2... i times bigger than the biggest one,
    // such that it is multiple of all the other numbers in the list
    std::cout << "The least common multiple of " << v << " is: " << lcm(v) << "\n\n";
}
