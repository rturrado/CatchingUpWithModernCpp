#ifndef __PRIORITY_QUEUE_H__
#define __PRIORITY_QUEUE_H__

#include <algorithm>  // make_heap, push_heap, pop_heap, swap
#include <functional>  // less
#include <vector>

template <typename T, typename Compare = std::less<T>>
class PriorityQueue
{
public:
    using Container = std::vector<T>;
    using container_type = Container;
    using value_compare = Compare;
    using value_type = Container::value_type;
    using size_type = Container::size_type;
    using reference = Container::reference;
    using const_reference = Container::const_reference;

private:
    /*
    // There is no way to iterate in order over a priority queue,
    // retrieving its top element in every iteration,
    // without modifying the queue
    //
    // The iterator below lets you walk a priority queue in order,
    // by first creating a copy of it and then sorting it
    // (sort would not be needed; we could do a pop for every iteration)
    class ConstIterator
    {
    public:
        using iterator_category = std::random_access_iterator_tag;
        using reference = Container::const_reference;

        using TPtr_ = size_type;

        constexpr ConstIterator() noexcept : ptr_{} {}
        constexpr ConstIterator(const PriorityQueue& pq, TPtr_ pos) noexcept
            : pq_{ pq }, ptr_{ pos }
        {
            std::sort_heap(pq_.container_.begin(), pq_.container_.end(), pq_.compare_);
        }
        constexpr reference operator*() const noexcept { return pq_.container_[ptr_]; }
        constexpr reference operator->() const noexcept { return pq_.container_[ptr_]; }
        constexpr ConstIterator& operator++() noexcept { ptr_++; return *this; }
        constexpr bool operator==(const ConstIterator& other) const noexcept
        {
            return pq_.container_ == other.pq_.container_ && ptr_ == other.ptr_;
        }
        constexpr bool operator<=>(const ConstIterator& other) const noexcept
        {
            return pq_.container_ == other.pq_.container_ and ptr_ <=> other.ptr_;
        }

    private:
        PriorityQueue<T, Compare> pq_{};
        TPtr_ ptr_{};
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
    };
    */

public:
    /*
    using const_iterator = ConstIterator;
    using iterator = Iterator;
    */
    using const_iterator = Container::const_iterator;
    using iterator = Container::iterator;

    PriorityQueue() = default;

    template <typename InputIt>
    PriorityQueue(InputIt first, InputIt last, const Compare& comp = Compare{})
        : container_{ first, last }, compare_{ comp }
    { std::make_heap(container_.begin(), container_.end(), compare_); }

    constexpr void push(const T& t) noexcept { container_.push_back(t); std::push_heap(container_.begin(), container_.end(), compare_); }
    constexpr void pop() noexcept { std::pop_heap(container_.begin(), container_.end(), compare_); container_.pop_back(); }
    [[nodiscard]] constexpr T& top() noexcept { return container_.front(); }
    [[nodiscard]] constexpr const T& top() const noexcept { return container_.front(); }
    [[nodiscard]] constexpr size_type size() const noexcept { return container_.size(); }
    [[nodiscard]] constexpr bool empty() const noexcept { return container_.empty(); }
    void swap(PriorityQueue& other) noexcept { std::swap(container_, other.container_); std::swap(compare_, other.compare_); }

    /*/
    constexpr iterator begin() noexcept { return Iterator{ *this, 0 }; }
    constexpr iterator end() noexcept { return Iterator{ *this, size() }; }
    constexpr const_iterator cbegin() const noexcept { return ConstIterator{ *this, 0 }; }
    constexpr const_iterator cend() const noexcept { return ConstIterator{ *this, size() }; }
    */
    constexpr iterator begin() noexcept { return container_.begin(); }
    constexpr iterator end() noexcept { return container_.end(); }
    constexpr const_iterator cbegin() const noexcept { return container_.cbegin(); }
    constexpr const_iterator cend() const noexcept { return container_.cend(); }

private:
    std::vector<T> container_{};
    Compare compare_{};
};

template <typename T, typename Compare>
void swap(PriorityQueue<T, Compare>& lhs, PriorityQueue<T, Compare>& rhs) noexcept(noexcept(lhs.swap(rhs))) { lhs.swap(rhs); }

template <typename T, typename Compare>
auto begin(PriorityQueue<T, Compare>& pq) -> decltype(pq.begin()) { return pq.begin(); }
template <typename T, typename Compare>
auto end(PriorityQueue<T, Compare>& pq) -> decltype(pq.end()) { return pq.end(); }
template <typename T, typename Compare>
auto cbegin(const PriorityQueue<T, Compare>& pq) -> decltype(pq.cbegin()) { return pq.cbegin(); }
template <typename T, typename Compare>
auto cend(const PriorityQueue<T, Compare>& pq) -> decltype(pq.cend()) { return pq.cend(); }

#endif
