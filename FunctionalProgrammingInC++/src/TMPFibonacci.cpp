#include <iostream>

#include "TMPFibonacci.h"

void tmp_fibonacci_main()
{
    std::cout << "fib(0) = " << Fibonacci<0>::value << "\n";
    std::cout << "fib(1) = " << Fibonacci<1>::value << "\n";
    std::cout << "fib(2) = " << Fibonacci<2>::value << "\n";
    std::cout << "fib(3) = " << Fibonacci<3>::value << "\n";
    std::cout << "fib(8) = " << Fibonacci<8>::value << "\n";
    std::cout << "fib(9) = " << Fibonacci<9>::value << "\n";
    std::cout << "fib(89) = " << Fibonacci<89>::value << "\n";
}