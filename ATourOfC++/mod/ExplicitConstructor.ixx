export module ExplicitConstructor;

import <iostream>;

namespace ExplicitConstructor
{
    class Vector
    {
    public:
        explicit Vector(int i) : i_{ i } {}
    private:
        int i_ = 10;
    };
}

using ExplicitConstructor::Vector;

export void explicit_constructor_main()
{
    //Vector v1 = 1;  // error: this would need an implicit conversion from int to Vector
    std::cout << "Can't implicitly convert from: " << typeid(1).name() << "\n";
    Vector v1 = Vector{ 1 };
    //Vector v2 = { 2 };  // error: this would need an implicit conversion from std::initializer_list<int> to Vector
    { auto v2 = { 2 };  std::cout << "Can't implicitly convert from: " << typeid(v2).name() << "\n"; }
    Vector v2 = Vector{ 2 };
    Vector v3{ 3 };
    Vector v4(4);
}
