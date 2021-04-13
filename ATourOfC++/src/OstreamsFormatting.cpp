#include <iomanip>
#include <iostream>

#include "OstreamsFormatting.h"

void ostreams_formatting_main()
{
    int i = 1234;
    int j = 5678;
    int k = 99999999;
    // Manipulators are sticky
    std::cout << std::hex << i << ' ' << j << "\n";
    std::cout << k << "\n";

    double d = 123.456789;
    std::cout << std::setprecision(5);
    std::cout << std::defaultfloat << d << "\n";
    std::cout << std::scientific << d << "\n";
    std::cout << std::fixed << d << "\n";

    // Precision does not affect integers
    std::cout << std::dec << k << "\n";
}
