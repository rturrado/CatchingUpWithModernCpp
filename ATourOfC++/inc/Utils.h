#ifndef __UTILS_H__
#define __UTILS_H__

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

template<typename T>
constexpr void PrintDeclarationAndType(std::string text, T var)
{
    std::cout << text << typeid(var).name() << "\n";
}

template<typename T>
inline constexpr std::string GetDeclarationAndTypeStr(std::string text, T var)
{
    std::ostringstream ss;
    ss << text << typeid(var).name() << "\n";
    return ss.str();
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::initializer_list<T>& l)
{
    os << "{";
    bool first = true;
    for (auto& d : l)
    {
        os << (first ? " " : ", ") << d;
        first = false;
    }
    os << " }";
    return os;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v)
{
    os << "{";
    bool first = true;
    for (const auto& d : v)
    {
        os << (first ? " " : ", ") << d;
        first = false;
    }
    os << " }";
    return os;
}

std::vector<int> read_vector_of_numbers_from_istream(std::istream& is);
std::vector<std::string> read_vector_of_strings_from_istream(std::istream& is);

#endif
