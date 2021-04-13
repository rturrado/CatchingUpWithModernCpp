#include "Span.h"

#include <memory>
#include <string>
#include <vector>

void span_main()
{
    std::string str{ "Hola mundo" };
    const char* c_str{ "Hi there Mombasa" };
    int c_arr[5]{ 1, 7, 19, 33, 85 };
    std::vector<std::string> vec{ "Happy", "birthday", "to", "you" };
    size_t size = 5;
    auto dbl_heap_arr = std::make_unique<double[]>(size);
    size_t i = 0;
    std::for_each(dbl_heap_arr.get(), dbl_heap_arr.get() + size, [&i](auto& n) { n = sqrt(i++); });

    print_span<const char>({ c_str, strlen(c_str) });
    print_span<char>(str);
    print_span<int>(c_arr);
    print_span<std::string>(vec);
    print_span<double>({ dbl_heap_arr.get(), size });

    // Modify span
    // Notice we are working over the original string
    // Like a pointer, a span does not own the characters it points to
    std::span<char> sp_char({ str.begin(), 4 });
    std::fill(sp_char.begin(), sp_char.end(), '!');
    print_span<char>(str);
}
