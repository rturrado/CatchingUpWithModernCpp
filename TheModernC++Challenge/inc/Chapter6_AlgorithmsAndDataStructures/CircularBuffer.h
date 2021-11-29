#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H

#include <algorithm>  // swap
#include <stdexcept>  // out_of_range
#include <vector>

template <typename T>
class CircularBuffer
{
public:
    using Container = std::vector<T>;
    using const_reference = Container::const_reference;
    using container_type = Container;
    using reference = Container::reference;
    using size_type = Container::size_type;
    using value_type = Container::value_type;

private:
    class ConstIterator
    {
    public:
        using iterator_category = std::random_access_iterator_tag;
        using reference = Container::const_reference;

        using TPtr_ = size_type;

        constexpr ConstIterator() noexcept : ptr_{} {}
        constexpr ConstIterator(const CircularBuffer& cb, TPtr_ pos, bool last) noexcept
            : cb_{ cb }, ptr_{ pos }, last_{ last } {}
        constexpr reference operator*() const noexcept { return cb_.container_[ptr_]; }
        constexpr reference operator->() const noexcept { return cb_.container_[ptr_]; }
        constexpr ConstIterator& operator++() noexcept
        {
            ptr_ = cb_.next_pos(ptr_);
            last_ = (ptr_ == cb_.next_pos(cb_.back_pos_));
            return *this;
        }
        constexpr ConstIterator operator++(int) noexcept
        {
            ConstIterator tmp{ *this };
            ++(*this);
            return tmp;
        }
        constexpr bool operator==(const ConstIterator& other) const noexcept
        {
            return &cb_ == &other.cb_ and last_ == other.last_ and ptr_ == other.ptr_;
        }
        constexpr bool operator<=>(const ConstIterator& other) const noexcept
        {
            return &cb_ == &other.cb_ and last_ == other.last_ and ptr_ <=> other.ptr_;
        }

    protected:
        const CircularBuffer<T>& cb_{};
        TPtr_ ptr_{ front_pos_ };
        // begin and end will point to the same position in a full circular buffer
        // This flag will help us differentiate them at the beginning of a loop
        bool last_{};
    };

    class Iterator : public ConstIterator
    {
        using MyBase_ = ConstIterator;

    public:
        using iterator_category = std::random_access_iterator_tag;
        using reference = Container::reference;

        constexpr reference operator*() const noexcept { return const_cast<reference>(MyBase_::operator*()); }
        constexpr reference operator->() const noexcept { return const_cast<reference>(MyBase_::operator->()); }
        constexpr Iterator& operator++() noexcept { MyBase_::operator++(); return *this; }
        constexpr Iterator operator++(int) noexcept { Iterator tmp{ *this }; MyBase_::operator++(); return tmp; }
    };

public:
    using const_iterator = ConstIterator;
    using iterator = Iterator;

    CircularBuffer(size_type capacity)
        : container_(capacity), capacity_{ capacity }
    {
        if (capacity_ == 0) { throw std::runtime_error{ "trying to create a CircularBuffer with a fixed size of 0." }; }
    }

    constexpr void push_back(const T& t) noexcept
    {
        back_pos_ = empty() ? front_pos_ : next_pos(back_pos_);
        if (full()) { front_pos_ = next_pos(front_pos_); }
        size_ = std::min(size_ + 1, capacity_);
        container_[back_pos_] = t;
    }
    constexpr void pop_front() { throw_if_empty(); front_pos_ = next_pos(front_pos_); size_--; }
    constexpr void pop_back() { throw_if_empty(); back_pos_ = prev_pos(back_pos_); size_--; }

    [[nodiscard]] constexpr T& front() { throw_if_empty(); return container_[front_pos_]; }
    [[nodiscard]] constexpr const T& front() const { throw_if_empty(); return container_[front_pos_]; }
    [[nodiscard]] constexpr T& back() { throw_if_empty(); return container_[back_pos_]; }
    [[nodiscard]] constexpr const T& back() const { throw_if_empty(); return container_[back_pos_]; }

    [[nodiscard]] constexpr size_type size() const noexcept { return size_; }
    [[nodiscard]] constexpr size_type capacity() const noexcept { return capacity_; }

    [[nodiscard]] constexpr bool empty() const noexcept { return size_ == 0; }
    [[nodiscard]] constexpr bool full() const noexcept { return size_ == capacity_; }

    constexpr void clear() noexcept { size_ = 0; }

    constexpr iterator begin() noexcept { return iterator{ *this, front_pos_, empty() }; }
    constexpr iterator end() noexcept { return iterator{ *this, empty() ? front_pos_ : next_pos(back_pos_), true }; }
    constexpr const_iterator cbegin() const noexcept { return const_iterator{ *this, front_pos_, empty() }; }
    constexpr const_iterator cend() const noexcept { return const_iterator{ *this, empty() ? front_pos_ : next_pos(back_pos_), true }; }

private:
    CircularBuffer() = default;

    [[nodiscard]] constexpr size_type next_pos(size_type pos) const noexcept { return (++pos % capacity_); }
    [[nodiscard]] constexpr size_type prev_pos(size_type pos) const noexcept { return (pos == 0) ? (capacity_ - 1) : --pos; }
    constexpr void throw_if_empty() const { if (empty()) { throw std::runtime_error{ "trying to access an empty CircularBuffer." }; } }

    std::vector<T> container_{};
    size_type size_{};
    size_type capacity_{};
    size_type front_pos_{};
    size_type back_pos_{};
};

template <typename T>
auto begin(CircularBuffer<T>& cb) -> decltype(cb.begin()) { return cb.begin(); }
template <typename T>
auto end(CircularBuffer<T>& cb) -> decltype(cb.end()) { return cb.end(); }
template <typename T>
auto cbegin(const CircularBuffer<T>& cb) -> decltype(cb.cbegin()) { return cb.cbegin(); }
template <typename T>
auto cend(const CircularBuffer<T>& cb) -> decltype(cb.cend()) { return cb.cend(); }

#endif  // CIRCULAR_BUFFER_H
