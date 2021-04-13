#include <string>

#include "TemplateFolds.h"

using TemplateFolds::print;

void template_folds_main()
{
    std::string blah = "hermano";
    double d = 3.141592;
    print("Hola", " ", blah, " ", d);

    // String blah was not moved because blah is an lvalue,
    // so it is treated as an lvalue reference in print(T&&... args)
    std::cout << "String after call with move: " << blah << "\n";
}
