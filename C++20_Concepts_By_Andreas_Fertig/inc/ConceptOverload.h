#ifndef __CONCEPT_OVERLOAD_H__
#define __CONCEPT_OVERLOAD_H__

#include <iostream>
#include <type_traits>

template<typename T>
concept class_type = std::is_class_v<T>;

template<typename T>
concept has_release = requires(T t)
{
    t.Release();
};

struct Empty
{};

struct COMLike
{
    void Release() {}
};

template<class_type T>
void Fun(const T&)
{
    std::cout << "Empty\n";
}

template<class_type T>
requires has_release<T>
void Fun(const T&)
{
    std::cout << "COMLike\n";
}

void concept_overload_main();

#endif
