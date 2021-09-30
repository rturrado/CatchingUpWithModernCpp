#ifndef __DOUBLE_BUFFER_H__
#define __DOUBLE_BUFFER_H__

#include <algorithm>  // copy
#include <mutex>
#include <vector>

template <typename T>
class DoubleBuffer
{
public:
    using Container = std::vector<T>;
    using Container_uptr = std::unique_ptr<Container>;

    using const_reference = Container::const_reference;
    using container_type = Container;
    using reference = Container::reference;
    using size_type = Container::size_type;
    using value_type = Container::value_type;

    DoubleBuffer() = default;
    explicit DoubleBuffer(size_type size)
        : buffer_write_(size)
        , buffer_read_(size)
        { }

    [[nodiscard]] constexpr size_type size() const noexcept { return buffer_read_.size(); }

    constexpr void write(size_type pos, const T& t)
    {
        buffer_write_[pos] = t;
        swap_buffers();
    }
    constexpr void write(size_type pos, const Container& v)
    {
        std::copy(cbegin(v), cend(v), begin(buffer_write_) + pos);
        swap_buffers();
    }
    [[nodiscard]] constexpr T read(size_type pos) const
    {
        std::scoped_lock sl{ buffers_mutex };
        return buffer_read_[pos];
    }
    [[nodiscard]] constexpr Container read(size_type pos, size_type size) const
    {
        std::scoped_lock sl{ buffers_mutex };
        Container ret(size);
        std::copy(cbegin(buffer_read_) + pos, cbegin(buffer_read_) + pos + size, begin(ret));
        return ret;
    }

private:
    constexpr void swap_buffers() noexcept
    {
        std::scoped_lock sl{ buffers_mutex };
        std::swap(buffer_write_, buffer_read_);
    }

    Container buffer_write_{};
    Container buffer_read_{};
    mutable std::mutex buffers_mutex{};
};

#endif
