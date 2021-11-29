#ifndef VARIADIC_TEMPLATES_H
#define VARIADIC_TEMPLATES_H

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

#endif  // VARIADIC_TEMPLATES_H
