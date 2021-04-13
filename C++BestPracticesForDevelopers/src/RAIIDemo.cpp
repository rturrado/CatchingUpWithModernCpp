#include <exception>

#include "RAIIDemo.h"

void raii_demo_main()
{
    Raii_demo r1{ 50 };
    Raii_demo r2{ 150 };
    throw std::runtime_error{"Allocation error!"};
}
