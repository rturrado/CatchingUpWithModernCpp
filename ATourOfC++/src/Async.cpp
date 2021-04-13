#include "Async.h"

#include <future>
#include <iostream>

void f() { for (int i = 0; i < 20; ++i) { std::cout << "."; } }
void g() { for (int i = 0; i < 20; ++i) { std::cout << "-"; } }

void async_main()
{
    // Next two lines should run concurrently but they don't
    //
    // The reason is that std::async returns a future and the ~future blocks until the execution of the std::async finishes
    // Since ~future happens before second std::async starts, execution of second std::async is blocked until first std::async finishes
    //
    // More into detail, std::async will set the value of a promise (or throw an exception), and a future will read that value
    // But, since the promise and the future could not coexist in time, the value is kept in a shared state
    // The standard states that the last future referring to a shared state should block until the thread for the asynchronously running function finishes
    // Note std::async will run its task in a separate thread
    //
    // https://stackoverflow.com/a/18143844/260313
    // http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2012/n3451.pdf
    // http://scottmeyers.blogspot.com/2013/03/stdfutures-from-stdasync-arent-special.html
    // https://en.cppreference.com/w/cpp/thread/future/~future
    std::cout << "First example: two non-concurrent asyncs: ";
    std::async([]() { f(); });  // ~future blocks
    std::async([]() { g(); });  // ~future blocks

    std::cout << "\n";
    
    // If we want actual concurrency we can just save the std::async return value
    // This way, f_future's destructor happens after std::async(g) is called
    std::cout << "Second example: two concurrent asyncs: ";
    auto f_future = std::async(f);
    auto g_future = std::async(g);
    // ~f_future, ~g_future
}
