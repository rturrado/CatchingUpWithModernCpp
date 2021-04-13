#include <string>

#include "MyEnum.h"

std::string color_to_str(const Color& color)
{
    std::string ret;

    switch (color)
    {
    case Color::green:
        ret = "green"; break;
    case Color::yellow:
        ret = "yellow"; break;
    case Color::red:
        ret = "red"; break;
    default:
        ret = "unknown"; break;
    }

    return ret;
}
