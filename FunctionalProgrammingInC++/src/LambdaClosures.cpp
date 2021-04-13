#include <iostream>

#include "LambdaClosures.h"

// A mutable total behaves as a static local variable
auto continuousAdd = [](auto initial, auto addBy)
{
    auto total = initial;
    return [total, addBy]() mutable
    {
        total += addBy;
        return total;
    };
};

void lambda_closures_main()
{
    auto cAdd = continuousAdd(1000, 10);
    std::cout << "Total = " << cAdd() << "\n";
    std::cout << "Total = " << cAdd() << "\n";
    std::cout << "Total = " << cAdd() << "\n";
    std::cout << "Total = " << cAdd() << "\n";
    std::cout << "Total = " << cAdd() << "\n";
}
