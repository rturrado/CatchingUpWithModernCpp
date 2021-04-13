#include <iostream>
#include <typeinfo>

#include "PointersArraysAndReferences.h"
#include "Utils.h"

int f(int) { return 0; }
int g() { return 0; }

void paar_main()
{
    // Arrays
    { char v[6]; PrintDeclarationAndType("char v[6]; type of v = ", v); }
    // Pointers
    { char v[6]; auto a = v; PrintDeclarationAndType("char v[6]; auto a = v; type of a = ", a); }
    // References
    { char v[6]; auto& r = v[3]; PrintDeclarationAndType("char v[6]; auto& r = v[3]; type of r = ", r); }
    // Functions
    { int f(1); PrintDeclarationAndType("int f(1); type of f = ", f); }  // int
    //{ int h(int); std::cout << GetDeclarationAndTypeStr("int f(int) { return 0; }; type of f = ", h); }  // function receiving int
    //{ int f(int); std::cout << "int f(int); type of f = " << typeid(f).name() << "\n"; }  // function receiving int
    { PrintDeclarationAndType("int g() { return 0; }; type of g = ", g); }  // function receiving nothing
    //{ int g(); std::cout << "int g(); type of g = " << typeid(g).name() << "\n"; }  // function receiving nothing
}
