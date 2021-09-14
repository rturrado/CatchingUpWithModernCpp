export module TemplateFolds;

import <iostream>;
import <string>;

namespace TemplateFolds
{
    // If a variable or parameter is declared to have type T&& for some deduced type T,
    // that variable or parameter is a universal reference.
    // https://isocpp.org/blog/2012/11/universal-references-in-c11-scott-meyers
    template<typename... T>
    void print(T&&... args)
    {
        (std::cout << ... << args) << '\n';  // print all arguments
    }
}  // end namespace TemplateFolds

using TemplateFolds::print;

export void template_folds_main()
{
    std::string blah = "hermano";
    double d = 3.141592;
    print("Hola", " ", blah, " ", d);

    // String blah was not moved because blah is an lvalue,
    // so it is treated as an lvalue reference in print(T&&... args)
    std::cout << "String after call with move: " << blah << "\n";
}
