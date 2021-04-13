#include "TypeInference.h"

#include <iostream>
#include <string>
#include <typeinfo>

template <typename lt, typename rt>
auto f(const lt& lhs, const rt& rhs)
{
    return lhs + rhs;
}

void type_inference_main()
{
    const char* cstr = "Hello world";
    std::string str = "Here's a greeting: ";
    auto x = f(str, cstr);

    std::cout << "x is: " << x << "\n";
    std::cout << "type of x is: " << typeid(x).name() << "\n";
}
