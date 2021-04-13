#ifndef __TEMPLATE_FOLDS_H__
#define __TEMPLATE_FOLDS_H__

#include <iostream>

namespace TemplateFolds
{
    // If a variable or parameter is declared to have type T&& for some deduced type T,
    // that variable or parameter is a universal reference.
    // https://isocpp.org/blog/2012/11/universal-references-in-c11-scott-meyers
    template<typename... T>
    void print(T&&... args) {
        (std::cout << ... << args) << '\n';  // print all arguments
    }
}  // end namespace TemplateFolds

void template_folds_main();

#endif
