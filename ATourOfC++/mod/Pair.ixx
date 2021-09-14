export module Pair;

import <algorithm>;
import <iostream>;
import <utility>;
import <string>;
import <vector>;

template <typename Forward_iterator>
void print_pair(const std::pair<Forward_iterator, int>& p)
{
    Forward_iterator it = p.first;
    for (int i = 0; i < p.second; ++i, ++it)
    {
        std::cout << (i ? " " : "") << *it;

    }
    std::cout << "\n";
}

template <typename Forward_iterator>
void print_pair(const std::pair<Forward_iterator, Forward_iterator>& p)
{
    bool first = false;
    std::for_each(p.first, p.second, [&first](const std::string& s) { std::cout << (first ? "" : " ") << s; first = false; });
    std::cout << "\n";
}

void f(std::vector<std::string>& v)
{
    std::pair p1{ v.begin() + 2, 2 }; // one way
    auto p2 = make_pair(v.begin(), 2); // another way
    auto p3 = make_pair(v.begin() + 1, v.end() - 1);
    print_pair(p1);  // calling print_pair(const pair<Forward_iterator, int>& p)
    print_pair(p2);  // calling print_pair(const pair<Forward_iterator, int>& p)
    print_pair(p3);  // calling print_pair(const pair<Forward_iterator, Forward_iterator>& p)
}

export void pair_main()
{
    std::vector<std::string> v{ "Hi,", "how", "are", "you!" };
    f(v);
}
