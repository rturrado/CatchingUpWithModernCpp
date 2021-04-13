#include "TemplateVariablesWithConstexpr.h"

#include <iostream>

template <typename T>
constexpr T pi = T(3.1415926535897932385L);

template <typename T>
constexpr T area_of_circle(const T& r)
{
    return r * r * pi<T>;
}

void template_variables_with_constexpr_main()
{
    std::cout.precision(20);

    // Option 1: area is calculated at running time
    std::cout << area_of_circle<long double>(3) << "\n";

    // Option 2: area is calculated at compile time
    constexpr auto area_of_3 = area_of_circle<long double>(3);
    std::cout << area_of_3 << "\n";
}
