#ifndef RTC_RANDOM_H
#define RTC_RANDOM_H

#include <concepts>  // floating_point
#include <random>
#include <string_view>


namespace rtc::random
{
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
    template <std::floating_point T = double>
    class RandomFloatingPoint
    {
    public:
        RandomFloatingPoint(T low, T high) : low_{ low }, high_{ high } {}
        T operator()()
        {
            return std::uniform_real_distribution<T>{ low_, high_ }(engine_);
        }
    private:
        T low_{ 0.0 };
        T high_{ 1.0 };
        std::default_random_engine engine_{ std::random_device{}() };
    };

    // Random letter generator
    // Generates a random letter
    // Valid letters are the white space and the 26 letters of the English alphabet, both in uppercase and lowercase
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
}  // namespace rtc::random


#endif  // RTC_RANDOM_H
