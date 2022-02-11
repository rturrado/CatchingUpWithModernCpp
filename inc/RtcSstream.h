#ifndef RTC_SSTREAM_H
#define RTC_SSTREAM_H

#include <sstream>  // istringstream

namespace rtc::sstream
{
    inline auto get_unread(std::istringstream& iss)
    {
        return iss.eof() ? "" : iss.str().substr(iss.tellg());
    }
}  // namespace rtc::sstream

#endif  // RTC_SSTREAM_H
