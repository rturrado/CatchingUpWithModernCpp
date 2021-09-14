export module ConstructorsAndDestructorsOrder;

import <iostream>;

struct C
{
    C() { std::cout << __FUNCTION__ << "\n"; }
    virtual ~C() { std::cout << __FUNCTION__ << "\n"; }
};

struct D : C
{
    D() { std::cout << __FUNCTION__ << "\n"; }
    virtual ~D() { std::cout << __FUNCTION__ << "\n"; }
};

struct E : D
{
    E() { std::cout << __FUNCTION__ << "\n"; }
    virtual ~E() { std::cout << __FUNCTION__ << "\n"; }
};

export void cado_main()
{
    C* c = new E();
    delete c;
}
