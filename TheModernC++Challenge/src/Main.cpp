#include "RtcConsoleRead.h"
#include "Problems.h"

#include <iostream>

int main()
{
    Problems& problems{ Problems::get_instance() };

    while (true)
    {
        // Read problem number
        auto n{ read_positive_number("Please enter a number (starting from 1): ", 1, problems.size() + static_cast<size_t>(1)) };

        // Execute problem
        std::cout << "\n[PROBLEM " << n << "]\n";
        problems.execute(n);
    }
}
