#include "IPv4.h"

#include <algorithm>
#include <ios>
#include <regex>
#include <sstream>

// Notes
// 
// uint8_t is an alias for unsigned char and thus treated as char by streams
// We use a temporary string in the string constructor, and a std::to_string conversion in the octets constructor

IPv4::IPv4(const std::string& address)
    // Initialize address
    : _address{ address }
{
    // Initialize array of octets
    std::istringstream iss{ _address };
    std::for_each(_octets.begin(), _octets.end(),
        [&iss, temp = std::string{}](uint8_t& n) mutable {
            std::getline(iss, temp, '.');
            n = std::stoi(temp);
        }
    );
}

IPv4::IPv4(uint8_t o0, uint8_t o1, uint8_t o2, uint8_t o3)
    // Initialize array of octets
    : _octets{ o0, o1, o2, o3 }
{
    // Initialize address
    std::ostringstream oss;
    std::for_each(_octets.cbegin(), _octets.cend(),
        [&oss, first = true](uint8_t n) mutable {
            oss << (first ? "" : ".") << std::to_string(n);
            first = false;
        }
    );
    _address = oss.str();
}

std::ostream& operator<<(std::ostream& os, const IPv4& ipv4)
{
    return os << ipv4._address;
}

std::istream& operator>>(std::istream& is, IPv4& ipv4)
{
    bool error{ false };

    // Read stream into a string
    std::string str{};
    is >> str;

    // Check string is a valid IPv4 address
    std::regex pattern{ R"(^([[:digit:]]{1,3})\.([[:digit:]]{1,3})\.([[:digit:]]{1,3})\.([[:digit:]]{1,3})$)" };
    std::smatch matches;
    if (std::regex_search(str, matches, pattern))
    {
        for (const std::string& match : matches)
        {
            if (std::stoi(match) > 255)
            {
                error = true;  // an octet is bigger than 255
                break;
            }
        }
    }
    else
    {
        error = true;  // string format is not correct
    }

    if (error)
    {
        is.setstate(std::ios_base::failbit);
        ipv4._address = std::string{};
    }
    else
    {
        ipv4._address = str;
    }

    return is;
}
