#ifndef __CONSTRUCTORS_H__
#define __CONSTRUCTORS_H__

struct Blah
{
    Blah(int i) { i_ = i; }
    Blah() = default;
    int i_ = 0;
private:
    Blah(const Blah& b) = default;
    Blah& operator=(const Blah& b) = default;
};

void constructors_main();

#endif
