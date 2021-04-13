#ifndef __CADO_H__
#define __CADO_H__

#include <iostream>

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

void cado_main();

#endif
