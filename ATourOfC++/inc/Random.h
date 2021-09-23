#ifndef __RANDOM_H__
#define __RANDOM_H__

#include <random>

// Random int generator
// Generates a random int in the range [low, high]
class RandomInt
{
public:
    RandomInt(int low, int high) : low_{ low }, high_{ high } {}
    int operator()()
    {
        return std::uniform_int_distribution<int>{ low_, high_ }(engine_);
    }
private:
    int low_{ 0 };
    int high_{ 1 };
    std::default_random_engine engine_{ std::random_device{}() };
};

// Random int generator
// Generates a random double in the range [low, high]
class RandomDouble
{
public:
    RandomDouble(double low, double high) : low_{ low }, high_{ high } {}
    double operator()()
    {
        return std::uniform_real_distribution<double>{ low_, high_ }(engine_);
    }
private:
    double low_{ 0.0 };
    double high_{ 1.0 };
    std::mt19937 engine_{ std::random_device{}() };
};

#endif
