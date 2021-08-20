#include <algorithm>
#include <array>
#include <iomanip>  // std::setfill, std::setw
#include <ios>  // std::hex
#include <iostream>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

#include "Utils.h"

template <typename Container>
std::string to_string(const Container& container)
requires (std::is_same_v<typename Container::value_type, uint8_t>)
{
    std::ostringstream oss{};
    std::for_each(cbegin(container), cend(container), [&oss](auto c) {
        oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<uint16_t>(c); });
    return oss.str();
}

// Binary to string conversion
// 
// Write a function that, given a range of 8-bit integers (such as an array or vector),
// returns a string that contains a hexadecimal representation of the input data.
// The function should be able to produce both uppercase and lowercase content.
// 
// Here are some input and output examples:
// Input: { 0xBA, 0xAD, 0xF0, 0x0D }, output: "BAADF00D" or "baadf00d"
// Input: { 1, 2, 3, 4, 5, 6 }, output: "010203040506"
void problem_23_main()
{
    std::vector<uint8_t> v{ 0xBA, 0xAD, 0xf0, 0x0d };
    std::cout << "Converting vector " << v << " to string \"" << to_string(v) << "\"\n";
    
    std::array<uint8_t, 6> a{};
    std::iota(begin(a), end(a), 1);
    std::cout << "Converting array " << a << " to string \"" << to_string(a) << "\"\n";
}
