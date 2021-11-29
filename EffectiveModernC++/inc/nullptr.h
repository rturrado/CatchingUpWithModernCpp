#ifndef NULLPTR_H
#define NULLPTR_H

#include <memory>

void f(int i);
void f(void* p);
void f(std::unique_ptr<int> up);

void f1(int i);
void f2(void* p);
void f3(std::unique_ptr<int> up);

template <typename FuncType, typename PtrType>
void g(FuncType func, PtrType ptr)
{
    func(ptr);
}

void nullptr_main();

#endif  // NULLPTR_H
