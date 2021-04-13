#include <iostream>

#include "MyClass.h"

MyClass::MyClass(size_t size)
    : size_{ size }
{
    // Do nothing
}

size_t MyClass::size()
{
    return size_;
}
