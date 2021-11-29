#ifndef MAKE_UNIQUE_H
#define MAKE_UNIQUE_H
#include <memory>

template<typename T, typename... Args>
requires std::is_constructible_v<T, Args...>
std::unique_ptr<T> make_unique(Args&&... args)
{
    return std::unique_ptr<T>(
        new T(std::forward<Args>(args)...));
}

struct X {};

struct Y {
    Y(int) {}
};

void make_unique_main();

#endif  // MAKE_UNIQUE_H
