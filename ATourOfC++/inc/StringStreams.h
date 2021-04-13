#ifndef __STRING_STREAMS_H__
#define __STRING_STREAMS_H__

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <typeinfo>

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

void string_streams_main();

#endif
