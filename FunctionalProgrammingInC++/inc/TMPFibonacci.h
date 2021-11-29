#ifndef TMP_FIBONACCI_H
#define TMP_FIBONACCI_H

template<int n>
struct Fibonacci
{
    enum { value = Fibonacci<n - 1>::value + Fibonacci<n - 2>::value };
};

template<>
struct Fibonacci<0>
{
    enum { value = 0 };
};

template<>
struct Fibonacci<1>
{
    enum { value = 1 };
};

void tmp_fibonacci_main();

#endif  // TMP_FIBONACCI_H
