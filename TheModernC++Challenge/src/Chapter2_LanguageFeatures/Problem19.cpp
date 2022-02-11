#include "Chapter2_LanguageFeatures.h"
#include "Chapter2_LanguageFeatures/Problem19.h"
#include "RtcPrint.h"

#include <iostream>  // cout
#include <list>
#include <string>
#include <vector>

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
    push_back_list_v2(l_float, 3.14f, 0.99f, -273.0f);
    std::cout << l_float << "\n";

    std::cout << "\n";
}
