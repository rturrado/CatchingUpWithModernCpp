export module Auto;

import <algorithm>;
import <iostream>;
import <typeinfo>;
import <vector>;

export void auto_main()
{
    { auto b = true; std::cout << "auto b = true; b = " << std::boolalpha << b << "; type of b = " << typeid(b).name() << "\n"; }
    { auto d = 1.2; std::cout << "auto d = 1.2; d = " << d << "; type of d = " << typeid(d).name() << "\n"; }
    { auto d = { 1.2 }; std::cout << "auto d = { 1.2 }; d = " << d << "; type of d = " << typeid(d).name() << "\n"; }  // std::initializer_list<double>
    { auto v = { 1, 2, 3 }; std::cout << "auto v = { 1, 2, 3 }; v = " << v << "; type of v = " << typeid(v).name() << "\n"; }  // std::initializer_list<int>
    // Error: braced initialization of a variable declared with a placeholder type but without '=' requires exactly one element inside the braces
    //{ auto v { 1, 2, 3 }; std::cout << "auto v { 1, 2, 3 }; type of v = " << typeid(v).name() << "\n"; }  // error 
    { auto v{ 1 }; std::cout << "auto v { 1 }; type of v = " << typeid(v).name() << "\n"; }  // int 
    { auto v(1); std::cout << "auto v(1); type of v = " << typeid(v).name() << "\n"; }  // int 
}
