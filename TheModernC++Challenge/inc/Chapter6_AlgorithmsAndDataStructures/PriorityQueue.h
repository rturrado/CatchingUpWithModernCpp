#ifndef __PRIORITY_QUEUE_H__
#define __PRIORITY_QUEUE_H__

#include <algorithm>  // sort
#include <functional>  // greater
#include <vector>

template <typename T, typename Compare = std::greater<T>>
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
    using iterator = Container::iterator;
    using const_iterator = Container::const_iterator;

    PriorityQueue() = default;

    template <typename InputIt>
    PriorityQueue(InputIt first, InputIt last, const Compare& comp = Compare{})
        : container_{ first, last }, compare_{ comp }
    { std::sort(container_.begin(), container_.end(), compare_); }

    constexpr void push(const T& t) noexcept { container_.push_back(t); std::sort(container_.begin(), container_.end(), compare_); }
    constexpr void pop() noexcept { container_.erase(container_.begin()); }
    [[nodiscard]] constexpr T& top() noexcept { return container_.front(); }
    [[nodiscard]] constexpr const T& top() const noexcept { return container_.front(); }
    [[nodiscard]] constexpr size_type size() const noexcept { return container_.size(); }
    [[nodiscard]] constexpr bool empty() const noexcept { return container_.empty(); }
    void swap(PriorityQueue& other) { container_.swap(other.container_); }

    constexpr iterator begin() noexcept { return container_.begin(); }
    constexpr iterator end() noexcept { return container_.end(); }
    constexpr const_iterator cbegin() const noexcept { return container_.cbegin(); }
    constexpr const_iterator cend() const noexcept { return container_.cend(); }

private:
    std::vector<T> container_{};
    Compare compare_{};
};

template <typename T, typename Compare = std::greater<T>>
auto begin(PriorityQueue<T, Compare>& pq) -> decltype(pq.begin()) { return pq.begin(); }
template <typename T, typename Compare = std::greater<T>>
auto end(PriorityQueue<T, Compare>& pq) -> decltype(pq.end()) { return pq.end(); }
template <typename T, typename Compare = std::greater<T>>
auto cbegin(const PriorityQueue<T, Compare>& pq) -> decltype(pq.cbegin()) { return pq.cbegin(); }
template <typename T, typename Compare = std::greater<T>>
auto cend(const PriorityQueue<T, Compare>& pq) -> decltype(pq.cend()) { return pq.cend(); }

#endif
