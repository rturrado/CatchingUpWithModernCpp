#include "Chapter2_LanguageFeatures.h"

#include <iostream>
#include <list>
#include <string>
#include <vector>

#include "Problem19.h"
#include "Utils.h"

// Adding a range of values to a container
// Write a general-purpose function that can add any number of elements
// to the end of a container that has a method push_back(T&& value).
void problem_19_main()
{
    std::vector<int> v_int{};
    push_back_list(v_int, 10, 20, 30);
    std::cout << v_int << "\n";

    std::vector<std::string> v_str{};
    push_back_list(v_str, "Hey", "Joe!", "Voodoo");
    std::cout << v_str << "\n";

    std::list<float> l_float{};
    push_back_list_v2(l_float, 3.14, 0.99, -273.0);
    std::cout << l_float << "\n";

    std::cout << "\n";
}
