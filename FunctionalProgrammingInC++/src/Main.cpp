#include <iostream>

#include "FilterAgesWithRxCpp.h"
#include "LambdaClosures.h"
#include "TMPFibonacci.h"

int main()
{
    // Lambda closures
    {
        std::cout << "[LAMBDA CLOSURES]\n";
        lambda_closures_main();
        std::cout << "\n";
    }

    // TMP Fibonacci
    {
        std::cout << "[TMP FIBONACCI]\n";
        tmp_fibonacci_main();
        std::cout << "\n";
    }

    // Filter ages with RxCpp
    {
        std::cout << "[FILTER AGES WITH RXCPP]\n";
        filter_ages_with_rx_cpp_main();
        std::cout << "\n";
    }
}
