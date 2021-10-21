#ifndef __RANDOM_H__
#define __RANDOM_H__

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
// Uppercase template parameter indicates is letter is lowercase or uppercase
// Valid letters are the 26 letters of the English alphabet plus the white space
template<bool Uppercase = false>
class RandomLetter
{
public:
    char operator()()
    {
        static std::string_view valid_letters{};

        if constexpr (Uppercase) { valid_letters = " ABCDEFGHIJKLMNOPQRSTUVWXYZ"; }
        else { valid_letters = " abcdefghijklmnopqrstuvwxyz"; }

        return valid_letters[std::uniform_int_distribution<size_t>{ 0, valid_letters.size() - 1 }(engine_)];
    }
private:
    std::default_random_engine engine_{ std::random_device{}() };
};

#endif
