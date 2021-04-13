#include "Constructors.h"

void constructors_main()
{
    Blah a{ 10 };
    //Blah b{ a };  // error: copy constructor is private
    Blah c;
    //c = { a };  // error: operator= is private
}
