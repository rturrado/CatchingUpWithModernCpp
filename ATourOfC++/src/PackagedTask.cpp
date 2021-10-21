#include "PackagedTask.h"
#include "Random.h"
#include "Utils.h"

#include <algorithm>
#include <future>
#include <iostream>
#include <numeric>
#include <thread>
#include <vector>

// Note the absence of explicit mention of locks in this code
// We are able to concentrate on tasks to be done, rather than on the mechanisms used to manage their communication
//
// Note as well the absence of explicit mention of promises in this code
// The packaged_task provides wrapper code to put the return value or exception from the task into a promise

double accum(double* beg, double* end, double init)
{
    // Compute the sum of [beg:end) starting with the initial value init
    return std::accumulate(beg, end, init);
}

void packaged_task_main()
{
    RandomDouble randomDouble{0.0, 20.0};
    std::vector<double> v(10);
    std::for_each(v.begin(), v.end(), [&randomDouble](double& n) { n = randomDouble(); });

    using Task_type = double(double*, double*, double);  // type of task
    std::packaged_task<Task_type> pt0{ accum };  // package the task (i.e., accum)
    std::packaged_task<Task_type> pt1{ accum };

    std::future<double> f0{ pt0.get_future() };  // get hold of pt0’s future
    std::future<double> f1{ pt1.get_future() };  // get hold of pt1’s future

    double* first = &v[0];
    std::thread t1{ move(pt0), first, first + v.size() / 2,0 };  // start a thread for pt0
    std::thread t2{ move(pt1), first + v.size() / 2, first + v.size(), 0 };  // start a thread for pt1

    double sum = f0.get() + f1.get();  // get the results

    t1.join();
    t2.join();

    std::cout << "Vector: " << v << "\n" << "Sum: " << sum << "\n";
}
