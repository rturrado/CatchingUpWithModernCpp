#include "ConstructorsAndDestructorsOrder.h"

void cado_main()
{
    C* c = new E();
    delete c;
}
