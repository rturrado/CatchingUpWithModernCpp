#include <iostream>
#include <string>

#include "StringStreams.h"

using StringStreams::to;

void string_streams_main()
{
    auto d = to(2.1);
    auto i = to(111);

    std::cout << "auto d = to(2.1) --> " << d << "\n";
    std::cout << "auto i = to(111) --> " << i << "\n";
}
