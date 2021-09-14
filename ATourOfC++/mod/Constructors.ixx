export module Constructors;

struct Blah
{
    Blah(int i) { i_ = i; }
    Blah() = default;
    int i_ = 0;
private:
    Blah(const Blah& b) = default;
    Blah& operator=(const Blah& b) = default;
};

export void constructors_main()
{
    Blah a{ 10 };
    //Blah b{ a };  // error: copy constructor is private
    Blah c;
    //c = a;  // error: operator= is private
}
