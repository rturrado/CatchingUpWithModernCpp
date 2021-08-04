#ifndef __PROBLEM_19_H__
#define __PROBLEM_19_H__

template <typename C, typename T>
concept ContainerWithPushBack = requires (C c, T t) { c.push_back(t); };

template <typename ContainerWithPushBack, typename T, typename = void>
void push_back_list(ContainerWithPushBack& c, T&& t)
{
    c.push_back(std::forward<T>(t));
}

template <typename ContainerWithPushBack, typename T, typename... Args>
void push_back_list(ContainerWithPushBack& c, T&& t, Args&&... args)
{
    c.push_back(std::forward<T>(t));
    push_back_list(c, std::forward<Args>(args)...);
}

// Using a fold expression as in the book
template <typename ContainerWithPushBack, typename... Args>
void push_back_list_v2(ContainerWithPushBack& c, Args... args)
{
    (c.push_back(args), ...);
}

#endif
