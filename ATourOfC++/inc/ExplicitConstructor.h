#ifndef __EXPLICIT_CONSTRUCTOR_H__
#define __EXPLICIT_CONSTRUCTOR_H__

namespace ExplicitConstructor
{
    class Vector
    {
    public:
        explicit Vector(int i) : i_{ i } {}
    private:
        int i_ = 10;
    };
}

void explicit_constructor_main();

#endif
