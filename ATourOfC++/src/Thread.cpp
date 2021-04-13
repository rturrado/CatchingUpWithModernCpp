#include "Thread.h"

#include <iostream>
#include <thread>
#include <vector>

namespace thread_example_1_ns
{
    void another_task() { std::cout << "another_task()\n"; }  // function
    class Task
    {
    public:
        void operator()() { std::cout << "Task::operator()\n"; }  // function object
    };
}

namespace thread_example_2_ns
{
    void f(std::vector<double>& v) { std::cout << "f\n"; }
    struct F {
        std::vector<double>& v;
        F(std::vector<double>& vv) :v{ vv } {}
        void operator()() { std::cout << "F::operator()\n"; }
    };
}

void thread_example_1()
{
    using namespace::thread_example_1_ns;

    std::thread t1{ another_task };
    std::thread t2{ Task{} };  // notice we are creating an object on the go and passing it

    t1.join();
    t2.join();
}

void thread_example_2()
{
    using namespace thread_example_2_ns;

    std::vector<double> some_vec{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    std::vector<double> vec2{ 10, 11, 12, 13, 14 };
    std::thread t1{ f, ref(some_vec) };
    std::thread t2{ F{vec2} };
    t1.join();
    t2.join();
}

void thread_main()
{
    thread_example_1();  // functions and function objects as tasks
    std::cout << "\n";
    thread_example_2();  // passing parameters
}
