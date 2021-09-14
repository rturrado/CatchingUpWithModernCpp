export module Random;

import <boost/uuid/uuid_generators.hpp>;
import <random>;

// Random int generator
// Generates a random int in the range [low, high]
export class RandomInt
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
export class RandomDouble
{
public:
    RandomDouble(double low, double high) : low_{ low }, high_{ high } {}
    double operator()()
    {
        return std::uniform_real_distribution<double>{ low_, high_ }( engine_ );
    }
private:
    double low_{ 0.0 };
    double high_{ 1.0 };
    std::mt19937 engine_{ std::random_device{}() };
};
