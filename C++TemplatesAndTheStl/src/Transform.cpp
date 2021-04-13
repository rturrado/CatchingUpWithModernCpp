#include "Transform.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

size_t sizeof_str(const std::string& s)
{
    return s.size();
}

void transform_main()
{
    // Using a functor object
    Accum<int> x;
    std::vector<int> v_int{ 1, 2, 3, 4, 5 };
    std::transform(v_int.begin(), v_int.end(), v_int.begin(), x);
    print_vector(v_int, "Functor object: ");

    // Creating the functor object in the same call
    std::transform(v_int.begin(), v_int.end(), v_int.begin(), Accum(15));
    print_vector(v_int, "Creating the functor object in the same call: ");

    // Using a lambda
    int accum = 50;
    std::transform(v_int.begin(), v_int.end(), v_int.begin(), [&accum](const int& n) { accum += n; return accum; });
    print_vector(v_int, "Lambda: ");

    // Using a function
    std::vector<std::string> v_str{ "one", "two", "three", "four", "five" };
    std::vector<size_t> result(v_str.size());
    std::transform(v_str.begin(), v_str.end(), result.begin(), sizeof_str);
    print_vector(result, "Function: ");
}