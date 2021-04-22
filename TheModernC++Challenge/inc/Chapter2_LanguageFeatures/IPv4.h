#ifndef __IPV4_H__
#define __IPV4_H__

#include <array>
#include <iostream>
#include <string>

// Notes
// 
// std::array is movable if its elements are movable
// That makes implementation of move constructor and move assignment operator unnecessary for the IPv4 class,
// since all the members are movable
// Copy construction, copy assignment operator and destructor are also unnecesary
// 
// operator<< and operator>> implemented as non-member functions and friends

class IPv4
{
public:
    IPv4() = default;
    explicit IPv4(const std::string& address);
    IPv4(uint8_t o0, uint8_t o1, uint8_t o2, uint8_t o3);
private:
    friend std::ostream& operator<<(std::ostream& os, const IPv4& ipv4);
    friend std::istream& operator>>(std::istream& is, IPv4& ipv4);

    std::string _address{};
    std::array<uint8_t, 4> _octets{};
};

#endif
