#include "Chapter2_LanguageFeatures.h"

#include <array>
#include <cassert>
#include <iostream>
#include <list>
#include <vector>

#include "Problem20.h"
#include "Utils.h"

// Container any, all, none
// Write a set of general-purpose functions that enable checking whether any, all, or none
// of the specified arguments are present in a given container.
void problem_20_main()
{
    std::vector<int> v{ 1, 2, 3, 4, 5, 6 };
    std::cout << "Checking std::vector<int> v{ 1, 2, 3, 4, 5, 6 } contains_any of (0, 3, 30)\n";
    assert(contains_any(v, 0, 3, 30));

    std::array<int, 6> a{ { 1, 2, 3, 4, 5, 6 } };
    std::cout << "Checking std::array<int, 6> a{ 1, 2, 3, 4, 5, 6 } contains_all of (1, 3, 5, 6)\n";
    assert(contains_all(a, 1, 3, 5, 6));

    std::list<int> l{ 1, 2, 3, 4, 5, 6 };
    std::cout << "Checking std::list<int> l{ 1, 2, 3, 4, 5, 6 } !contains_none of (0, 6)\n";
    assert(!contains_none(l, 0, 6));

    std::cout << "\n";
}
