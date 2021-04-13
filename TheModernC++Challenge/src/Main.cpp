#include <array>
#include <iostream>
#include <functional>

#include "Chapter1_MathProblems.h"
#include "Problems.h"
#include "Utils.h"

int main()
{
/*
    // Problem 1
    { std::cout << "[PROBLEM 1]\n"; while (true) { problem_1_main(); } std::cout << "\n"; }
    // Problem 2
    { std::cout << "[PROBLEM 2]\n"; while (true) { problem_2_main(); } std::cout << "\n"; }
    // Problem 3
    { std::cout << "[PROBLEM 3]\n"; while (true) { problem_3_main(); } std::cout << "\n"; }
    // Problem 4
    { std::cout << "[PROBLEM 4]\n"; while (true) { problem_4_main(); } std::cout << "\n"; }
    // Problem 5
    { std::cout << "[PROBLEM 5]\n"; while (true) { problem_5_main(); } std::cout << "\n"; }
    // Problem 6
    { std::cout << "[PROBLEM 6]\n"; while (true) { problem_6_main(); } std::cout << "\n"; }
*/

 /*
    using FunctionType = std::function<void()>;
    std::array<FunctionType, 100> problems{};
    problems[0] = problem_1_main;
    problems[1] = problem_2_main;
    problems[2] = problem_3_main;
    problems[3] = problem_4_main;
    problems[4] = problem_5_main;
    problems[5] = problem_6_main;
*/

    Problems problems{};

    while (true)
    {
        // Read problem number
        auto n{ read_positive_number(1, problems.size() + static_cast<size_t>(1)) };

        // Execute problem
        std::cout << "[PROBLEM " << n << "]\n";
        problems.execute(n);
    }
}
