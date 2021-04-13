#ifndef __RANDOM_H__
#define __RANDOM_H__

#include <boost/uuid/uuid_generators.hpp>
#include <random>

// Random int generator
// Generates a random int in the range [low, high]
class RandomInt
{
public:
    RandomInt(int low, int high) : dist_{ low, high } {}
    int operator()() { return dist_(engine_); }
private:
    std::default_random_engine engine_;
    std::uniform_int_distribution<> dist_;
};

// Random int generator
// Generates a random int in the range [low, high]
class RandomDouble
{
public:
    RandomDouble(double low, double high) : dist_{ low, high } {}
    double operator()() { return dist_(engine_); }
private:
    std::default_random_engine engine_;
    std::uniform_real_distribution<double> dist_;
};

#endif
