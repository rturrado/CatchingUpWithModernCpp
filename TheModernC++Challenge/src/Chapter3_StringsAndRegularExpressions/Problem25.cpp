#include "Chapter3_StringsAndRegularExpressions.h"

#include <algorithm>  // for_each
#include <cctype>  // isalpha, tolower, toupper
#include <format>
#include <iostream>  // cout
#include <string>

std::string capitalize(const std::string& s)
{
    std::string ret{s};
    std::for_each(begin(ret), end(ret), [parsing_word = false](char& c) mutable {
        if (parsing_word)
        {
            // End of word. Update parsing word flag
            if (not std::isalpha(c))
            {
                parsing_word = false;
            }
            // Else, just another word char
            {
                c = std::tolower(c);
            }
        }
        else 
        {
            // First word char. Capitalize it and update parsing word flag
            if (std::isalpha(c))
            {
                c = std::toupper(c);
                parsing_word = true;
            }
            // Else, just another non word char
        }
    });
    return ret;
}

// Capitalizing an article title
// 
// Write a function that transforms an input text into a capitalized version,
// where every word starts with an uppercase letter and has all the other letters in lowercase.
// For instance, the text "the c++ challenger" should be transformed to "The C++ Challenger".
void problem_25_main()
{
    std::string s1{ "the c++ challenger" };
    std::string s2{ "THIS IS an ExamplE, should wORk!" };
    std::cout << std::format("Capitalizing word \"{}\": \"{}\"", s1, capitalize(s1)) << "\n";
    std::cout << std::format("Capitalizing word \"{}\": \"{}\"", s2, capitalize(s2)) << "\n";
    std::cout << "\n";
}
