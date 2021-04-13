#include "rxcpp/rx.hpp"

#include "FilterAgesWithRxCpp.h"

namespace Rx {
    using namespace rxcpp;
    using namespace rxcpp::sources;
    using namespace rxcpp::operators;
    using namespace rxcpp::util;
}
using namespace Rx;

void filter_ages_with_rx_cpp_main()
{
    std::vector<int> ages{9, 20, 13, 4, 5, 6, 10, 28, 19, 15, 60, 23, 47, 12, 19, 99};
    size_t count = 0;
    auto values = rxcpp::observable<>::iterate(ages).  // chaining
        filter([](int age) {return age >= 13 && age <= 19; }).
        subscribe(
            [&count](int n) { count++;  std::cout << count << ": " << n << "\n"; },  // lambda called to handle every event
            []() { std::cout << "End of example\n"; }  // lambda called when observable is complete
    );
}
