#ifndef __TEMPLATE_ARGUMENT_DEDUCTION_H__
#define __TEMPLATE_ARGUMENT_DEDUCTION_H__

#include <iostream>

#include "Utils.h"

namespace TemplateArgumentDeduction
{
    template <typename T>
    concept Printable = requires(std::ostream& os, T a)    { os << a; };

    template <Printable T>
    class Vector
    {
    public:
        Vector(int i)  // note we are not defining Vector(T t)
        {
            std::cout << "* Vector(int i): " << i << "\n";
        };
        Vector(std::initializer_list<T> l)
        {
            std::cout << "* Vector(std::initializer_list<T> l): " << l << "\n";
        };
    private:
    };
}

void template_argument_deduction_main();

#endif
