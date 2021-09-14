export module MyEnum;

import <string>;

export enum class Color { green, yellow, red };

export std::string color_to_str(const Color& color)
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
