#ifndef __MY_CLASS_H__
#define __MY_CLASS_H__

class MyClass
{
public:
    MyClass() = default;
    MyClass(size_t size);
    size_t size();
private:
    size_t size_ = 20;
};

#endif
