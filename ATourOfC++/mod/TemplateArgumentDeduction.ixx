export module TemplateArgumentDeduction;

import <initializer_list>;
import <iostream>;
import <typeinfo>;

import Utils;

namespace TemplateArgumentDeduction
{
    template <typename T>
    concept Printable = requires(std::ostream& os, T a) { os << a; };

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

using TemplateArgumentDeduction::Vector;

export void template_argument_deduction_main()
{
    Vector v1{ 1, 2, 3 }; std::cout << "\tVector v1{ 1, 2, 3}; type of v1 = " << typeid(v1).name() << "\n";
    Vector v2 = v1; std::cout << "\tVector v2 = v1; type of v2 = " << typeid(v2).name() << "\n";
    auto p = new Vector{ 1, 2, 3 }; std::cout << "\tauto p = new Vector{1, 2, 3}; type of p = " << typeid(p).name() << "\n";
    //Vector v3(1); std::cout << "\tVector v3(1); type of v3 = " << typeid(v3).name() << "\n";  // error: from what template instantiation do you want to use Vector(int)?
    Vector<int> v3(1); std::cout << "\tVector<int> v3(1); type of v3 = " << typeid(v3).name() << "\n";

    Vector<std::initializer_list<int>> v4 = { { 1, 2, 3 } }; std::cout << "\tVector<std::initializer_list<int>> v4 = { { 1, 2, 3} }; type of v4 = " << typeid(v4).name() << "\n";
    Vector v5 = { { 1, 2, 3 } }; std::cout << "\tVector v5 = { { 1, 2, 3} }; type of v5 = " << typeid(v5).name() << "\n";
    Vector v6({ 1 }); std::cout << "\tVector v6({ 1 }); type of v6 = " << typeid(v6).name() << "\n";
    //Vector v7({ { 1 } }); std::cout << "\tVector v7({ { 1 } }); type of v7 = " << typeid(v7).name() << "\n";  // syntax error
    Vector v8{ 1.2 }; std::cout << "\tVector v8{ 1.2 }; type of v8 = " << typeid(v8).name() << "\n";
}
