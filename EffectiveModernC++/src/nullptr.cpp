#include "nullptr.h"

#include <iostream>

void f(int i) { std::cout << "f(int)\n"; }
void f(void* p) { std::cout << "f(void*)\n"; }
void f(std::unique_ptr<int> up) { std::cout << "f(std::unique_ptr<int>)\n"; }

void f1(int i) { std::cout << "f1(int)\n"; }
void f2(void* p) { std::cout << "f2(void*)\n"; }
void f3(std::unique_ptr<int> up) { std::cout << "f3(std::unique_ptr<int>)\n"; }

void nullptr_main()
{
    f(0);  // f(int)
    f(NULL);  // f(int) in VS2019, error in clang++-7 (call to 'f' is ambiguous)
    f(nullptr);  // f(void*)

    //int i = 0;
    //f2(i);  // error: cannot convert from from 'int' to 'void *'

    //g(f3, 0);  // error: cannot convert from 'int' to 'std::unique_ptr<int>'
    //g(f3, NULL);  // error: cannot convert from 'int' to 'std::unique_ptr<int>'
    g(f3, nullptr);
}
