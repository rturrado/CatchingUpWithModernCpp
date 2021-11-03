#ifndef __PROBLEM_20_H__
#define __PROBLEM_20_H__

#include <algorithm>  // find

template <typename C, typename... Args>
bool contains_any(C& c, Args&&... args)
{
    return (... or (std::find(cbegin(c), cend(c), args) != cend(c)));
}

template <typename C, typename... Args>
bool contains_all(C& c, Args&&... args)
{
    return (... and (std::find(cbegin(c), cend(c), args) != cend(c)));
}

template <typename C, typename... Args>
bool contains_none(C& c, Args&&... args)
{
    return (... and (std::find(cbegin(c), cend(c), args) == cend(c)));
}

#endif
