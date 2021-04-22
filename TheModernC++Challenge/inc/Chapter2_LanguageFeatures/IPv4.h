#ifndef __IPV4_H__
#define __IPV4_H__

#include <array>
#include <iostream>
#include <regex>
#include <string>

class IPv4
{
public:
    IPv4() = default;
    explicit IPv4(const std::string& address);
    IPv4(uint8_t o0, uint8_t o1, uint8_t o2, uint8_t o3);
    IPv4(IPv4&& rhs) noexcept;
    IPv4& operator=(IPv4&& rhs) noexcept;
    std::string to_string() const;
private:
    std::string _address{};
    std::array<uint8_t, 4> _octets{};
};

std::ostream& operator<<(std::ostream& os, const IPv4& address);
std::istream& operator>>(std::istream& is, IPv4& address);

#endif
