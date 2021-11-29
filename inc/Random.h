#ifndef RANDOM_H
#define RANDOM_H

#include <random>
#include <string_view>

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

// Random double generator
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
    std::default_random_engine engine_{ std::random_device{}() };
};

// Random letter generator
// Generates a random letter
// Valid letters are the white space and the 26 letters of the English alphabet, both in uppercase and lowercase
template<bool Uppercase = false>
class RandomLetter
{
public:
    char operator()()
    {
        // Notice the first letter is intentionally blank
        static const std::string_view valid_letters{ " abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ" };

        return valid_letters[std::uniform_int_distribution<size_t>{ 0, valid_letters.size() - 1 }(engine_)];
    }
private:
    std::default_random_engine engine_{ std::random_device{}() };
};

#endif  // RANDOM_H
