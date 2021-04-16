#include "LinkedList.h"

#include <iostream>

void linked_list_main()
{
    LinkedList<int> ll_int{};
    ll_int.push_front(5);
    ll_int.push_back(10);
    std::cout << ll_int << "\n";

    LinkedList<std::string> ll_str{};
    ll_str.push_front("Hola");
    ll_str.push_back("Juan");
    std::cout << ll_str << "\n";
}
