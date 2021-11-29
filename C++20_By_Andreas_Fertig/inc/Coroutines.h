#ifndef COROUTINES_H
#define COROUTINES_H

#include <coroutine>
#include <iostream>
#include <numeric>

template <typename PromiseType>
struct MyIterator {
    using CoHandle = std::coroutine_handle<PromiseType>;
    CoHandle mHdl{};
    
    void resume() { if (!mHdl.done()) { mHdl.resume(); } }

    MyIterator() = default;
    MyIterator(const CoHandle& h) : mHdl{ h } { resume(); }

    MyIterator& operator++() { resume(); return *this; }
    bool operator==(const MyIterator&) const { return mHdl.done(); }
    const auto& operator*() const { return mHdl.promise().mValue; }
    const auto* operator->() const { return &(mHdl.promise().mValue); }
};

template <typename Generator>
struct MyPromise
{
    Generator::type mValue;

    std::suspend_always yield_value(Generator::type value)
    {
        mValue = std::move(value);
        return {};
    }
    std::suspend_always initial_suspend() { return {}; }
    std::suspend_always final_suspend() noexcept { return {}; }
    Generator get_return_object() { return Generator{ this }; }
    void return_void() {}
    void unhandled_exception() { std::terminate(); }
};

template <typename T>
struct MyGenerator
{
    using type = T;

    using promise_type = MyPromise<MyGenerator>;
    using handle = std::coroutine_handle<promise_type>;
    using iterator = MyIterator<promise_type>;

    iterator begin() { return { mCoHandle }; }
    iterator end() { return {}; }
    const iterator cbegin() const { return { mCoHandle }; }
    const iterator cend() const { return {}; }

    MyGenerator(MyGenerator&& rhs) : mCoHandle{ std::exchange(rhs.mCoHandle, nullptr) } {}
    ~MyGenerator() { if (mCoHandle) { mCoHandle.destroy(); } }

private:
    friend promise_type;
    explicit MyGenerator(promise_type* p) : mCoHandle{ handle::from_promise(*p) } {}

    handle mCoHandle;
};

template <typename T>
MyGenerator<T> seq()
{
    for (T i{}; ; ++i)
    {
        co_yield i;
    }
}

template <typename T>
MyGenerator<T> take_until(MyGenerator<T>& g, const T& limit)
{
    for (auto&& i : g)
    {
        if (i < limit)
        {
            co_yield i;
        }
        else
        {
            break;
        }
    }
}

template <typename T>
MyGenerator<T> multiply(MyGenerator<T>& g, const T& factor)
{
    for (auto&& i : g)
    {
        co_yield i * factor;
    }
}

void coroutines_main()
{
    auto seq_co{ seq<int>() };
    auto take_until_co{ take_until(seq_co, 10) };
    auto multiply_co{ multiply(take_until_co, 2) };

    auto result = std::accumulate(multiply_co.cbegin(), multiply_co.cend(), 0);
    std::cout << "Multiplies: " << result << "\n";
}

#endif  // COROUTINES_H
