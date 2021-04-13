#ifndef __VARIADIC_TEMPLATES_H__
#define __VARIADIC_TEMPLATES_H__

// Base case
template<typename T>
T summer(T v)
{
    return v;
}

// Recursive case
template<typename T, typename... Args>
T summer(T first, Args... args)
{
    return first + summer(args...);
}

#endif
