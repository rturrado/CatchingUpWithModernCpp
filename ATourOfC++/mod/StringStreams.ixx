export module StringStreams;

import <iostream>;
import <sstream>;
import <stdexcept>;
import <string>;
import <typeinfo>;

namespace StringStreams
{
    template<typename Target = std::string, typename Source = std::string>
    Target to(Source arg)  // convert Source to Target
    {
        std::stringstream interpreter;
        Target result;

        std::cout << "Converting from " << typeid(arg).name() << " to " << typeid(result).name() << "\n";

        if (!(interpreter << arg)  // write arg into stream
            || !(interpreter >> result)  // read result from stream
            || !(interpreter >> std::ws).eof())  // stuff left in stream?
            throw std::runtime_error{ "to<>() failed" };
        return result;
    }
}

using StringStreams::to;

export void string_streams_main()
{
    auto d = to(2.1);
    auto i = to(111);

    std::cout << "auto d = to(2.1) --> " << d << "\n";
    std::cout << "auto i = to(111) --> " << i << "\n";
}
