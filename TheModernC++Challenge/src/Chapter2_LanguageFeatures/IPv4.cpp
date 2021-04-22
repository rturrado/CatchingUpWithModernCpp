#include "IPv4.h"

#include <algorithm>
#include <ios>
#include <sstream>

IPv4::IPv4(const std::string& address)
    // Initialize address
    : _address{ address }
{
    // Initialize array of octets
    std::istringstream iss{ _address };
    std::for_each(_octets.begin(), _octets.end(), [&iss](uint8_t& n) { iss >> n; });
}

IPv4::IPv4(uint8_t o0, uint8_t o1, uint8_t o2, uint8_t o3)
{
    // Initialize array of octets
    _octets[0] = o0;
    _octets[1] = o1;
    _octets[2] = o2;
    _octets[3] = o3;

    // Initialize address
    std::ostringstream oss;
    std::for_each(_octets.begin(), _octets.end(),
        [&oss, first = true](uint8_t n) mutable { oss << (first ? "" : ".") << n; first = false; });
}

IPv4::IPv4(IPv4&& rhs) noexcept
    : _address{ std::move(rhs._address) }
    , _octets{ std::move(rhs._octets) }
{
    // Do nothing
}

IPv4& IPv4::operator=(IPv4&& rhs) noexcept
{
    _address = std::move(rhs._address);
    _octets = std::move(rhs._octets);
    return *this;
}

std::string IPv4::to_string() const
{
    return _address;
}

std::ostream& operator<<(std::ostream& os, const IPv4& address)
{
    return os << address.to_string();
}

std::istream& operator>>(std::istream& is, IPv4& address)
{
    bool error{ false };

    // Read stream into a string
    std::string str{};
    is >> str;

    // Check string is a valid IPv4 address
    std::regex pattern{ R"(^([[:digit:]]{1,3})\.([[:digit:]]{1,3})\.([[:digit:]]{1,3})\.([[:digit:]]{1,3})$)" };
    std::smatch matches;
    if (std::regex_search(str, matches, pattern))  // format is correct
    {
        for (const std::string& match : matches)
        {
            if (std::stoi(match) > 255)  // every number is not bigger than 255
            {
                error = true;
                break;
            }
        }
    }
    else
    {
        error = true;
    }
    if (error)
    {
        is.setstate(std::ios_base::failbit);
    }
    else
    {
        IPv4 temp{ str };
        address = std::move(temp);
    }
    return is;
}
