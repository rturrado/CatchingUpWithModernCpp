#include "LinkedList.h"

#include <iostream>

void linked_list_main()
{
    LinkedList<int> ll_int{};
    ll_int.push_front(5);
    ll_int.push_back(10);
    std::cout << ll_int << "\n";

    ll_int.clear();

    LinkedList<std::string> ll_str{};
    ll_str.push_front("Hola");
    ll_str.push_back("Juan");
    ll_str.push_back("Yo");
    ll_str.push_back("Dave");
    std::cout << ll_str << "\n";
    std::cout << ll_str.front() << "\n";
    std::cout << ll_str.back() << "\n";
    ll_str.pop_front();
    ll_str.pop_back();
    std::cout << ll_str << "\n";
}
