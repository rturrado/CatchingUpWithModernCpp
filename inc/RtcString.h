#ifndef RTC_STRING_H
#define RTC_STRING_H

#include <algorithm>  // transform
#include <cctype>  // tolower
#include <string>

namespace rtc::string
{
    inline void to_lowercase(std::string& str)
    {
        std::ranges::transform(str, std::begin(str), [](unsigned char c) { return std::tolower(c); });
    }
}  // namespace rtc::string

#endif  // RTC_STRING_H
