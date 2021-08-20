#include <cassert>
#include <string>
#include <vector>

#include "Utils.h"

uint8_t to_binary(char c)
{
    uint8_t ret{ 0 };

    if ('0' <= c and c <= '9') { ret = c - '0'; }
    else if ('a' <= c and c <= 'f') { ret = c - 'a' + 10; }
    else if ('A' <= c and c <= 'F') { ret = c - 'A' + 10; }

    return ret;
}

std::vector<uint8_t> to_binary(const std::string& s)
{
    assert(("String has an odd number of characters", s.size() % 2 == 0));

    std::vector<uint8_t> ret(s.size() / 2);

    for (size_t i{ 0 }; i < (s.size() / 2); ++i)
    {
        auto top_nibble{ to_binary(s[static_cast<size_t>(i * 2)]) };
        auto bottom_nibble{ to_binary(s[static_cast<size_t>(i * 2 + 1)]) };
        uint8_t n{ static_cast<uint8_t>((top_nibble << 4) + bottom_nibble) };
        ret[i] = n;
    }

    return ret;
}

// String to binary conversion
//
// Write a function that, given a string containing hexadecimal digits as the input argument,
// returns a vector of 8-bit integers that represent the numerical deserialization of the string content.
//
// The following are examples:
// Input: "BAADF00D" or "baadf00d", output: { 0xBA, 0xAD, 0xF0, 0x0D }
// Input: "010203040506", output: { 1, 2, 3, 4, 5, 6 }
void problem_24_main()
{
    std::string s1{ "BAADf00d" };
    std::string s2{ "010203040506" };

    std::cout << "Converting string \"" << s1 << "\" to vector " << to_binary(s1) << "\n";
    std::cout << "Converting string \"" << s2 << "\" to vector " << to_binary(s2) << "\n";
    //std::cout << to_binary("10203") << "\n";
}
