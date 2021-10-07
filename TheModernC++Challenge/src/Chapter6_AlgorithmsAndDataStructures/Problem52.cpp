#include <algorithm>  // for_each, sort, next_permutation
#include <iostream>  // cout
#include <string>
#include <vector>

using permutations = std::vector<std::string>;

permutations all_permutations_rec_impl(std::string str)
{
    permutations ret{};
    if (str.size() == 1) { ret.push_back(str); }
    else
    {
        for (const auto& s : all_permutations_rec_impl(str.substr(1)))
        {
            for (auto i{ 0 }; i <= s.size(); ++i)
            {
                ret.push_back(s.substr(0, i) + str[0] + s.substr(i));
            }
        }
    }
    return ret;
}

permutations all_permutations_rec(const std::string& str)
{
    if (str.empty()) { return {}; }

    auto str_copy{ str };
    std::sort(begin(str_copy), end(str_copy));
    return all_permutations_rec_impl(str_copy);
}

permutations all_permutations(const std::string& str)
{
    if (str.empty()) { return {}; }

    permutations ret{};
    auto str_copy{ str };
    std::sort(begin(str_copy), end(str_copy));
    do { ret.push_back(str_copy); } while (std::next_permutation(begin(str_copy), end(str_copy)));
    return ret;
}

// Generating all the permutations of a string
//
// Write a function that prints on the console all the possible permutations of a given string.
// You should provide two versions of this function: one that uses recursion, and one that does not.
void problem_52_main()
{
    for (const auto& str : { "", "n", "ab", "andy" })
    {
        std::cout << "All permutations of string: " << str << "\n";

        std::cout << "\t1) Using recursion:\n";
        permutations apr{ all_permutations_rec(str) };
        std::for_each(cbegin(apr), cend(apr), [first = true](const auto& s) mutable {
            std::cout << (first ? "\t\t" : ", ") << s; first = false;
        });
        std::cout << "\n";

        std::cout << "\t2) Not using recursion:\n";
        permutations ap{ all_permutations(str) };
        std::for_each(cbegin(ap), cend(ap), [first = true](const auto& s) mutable {
            std::cout << (first ? "\t\t" : ", ") << s; first = false;
        });
        std::cout << "\n\n";
    }
}
