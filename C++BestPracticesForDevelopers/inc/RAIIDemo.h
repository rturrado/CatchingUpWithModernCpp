#ifndef RAII_DEMO_H
#define RAII_DEMO_H

#include <iostream>

class Raii_demo
{
public:
    explicit Raii_demo(int i) : i_{ i }    { std::cout << "Raii_demo(int " << i_ << ")\n"; }
    ~Raii_demo() { std::cout << "~Raii_demo: " << i_ << "\n"; }
private:
    int i_;
};

void raii_demo_main();

#endif  // RAII_DEMO_H
