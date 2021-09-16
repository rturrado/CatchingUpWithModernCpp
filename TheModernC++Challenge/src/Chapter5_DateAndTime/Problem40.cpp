#include <chrono>
#include <iostream>

// Number of days between two dates
//
// Write a function that, given two dates, returns the number of days between the two dates.
// The function should work regardless of the order of the input dates.
void problem_40_main()
{
    using namespace std::chrono;

    auto x{ 2012y / 1 / 24 };
    auto y{ 2013y / 1 / 8 };

    if (x > y)
    {
        std::swap(x, y);
    }

    std::cout << "First day: " << x << "\n";
    std::cout << "Second day: " << y << "\n";
    std::cout << "Difference (in days): " << (std::chrono::sys_days{ y } - std::chrono::sys_days{ x }).count() << "\n";
    std::cout << "\n";
}
