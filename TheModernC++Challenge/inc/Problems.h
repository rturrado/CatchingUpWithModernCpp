#ifndef __PROBLEMS_H__
#define __PROBLEMS_H__

#include <cassert>
#include <functional>
#include <array>

class Problems
{
    static const size_t maxNumberOfProblems{ 100 };
    using FunctionType = std::function<void()>;
    using ArrayOfProblemsType = std::array<FunctionType, Problems::maxNumberOfProblems>;
public:
    Problems();
    FunctionType& operator[](const size_t pos)
    {
        return _arr[pos];
    }
    size_t size()
    {
        return _size;
    }
    void execute(size_t i)
    {
        assert((i > 0) && (i <= _size));
        std::invoke(_arr[i - 1]);
    }
private:
    ArrayOfProblemsType _arr{};
    size_t _size{ 0 };
};

#endif
