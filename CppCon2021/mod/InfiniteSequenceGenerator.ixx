// References: Conquering C++20 Ranges; Tristan Brindle; CppCon 2021

module;

#include <utility>  // exchange

export module InfiniteSequenceGenerator;

export class InfiniteSequenceGenerator
{
public:
    InfiniteSequenceGenerator(int first, int step) : current_{ first }, step_{ step } {}
    int operator()() { return std::exchange(current_, current_ + step_); }
private:
    int current_{ 0 };
    int step_{ 1 };
};
