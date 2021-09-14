export module MyClass;

import <iostream>;

export class MyClass
{
public:
    MyClass() = default;
    MyClass(size_t size);
    size_t size();
private:
    size_t size_ = 20;
};

MyClass::MyClass(size_t size)
    : size_{ size }
{
    // Do nothing
}

size_t MyClass::size()
{
    return size_;
}
