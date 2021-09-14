export module Initialization;

import <iostream>;
import <vector>;

import Utils;

export void initialization_main()
{
    { int i = 3.7; std::cout << "int i = 3.7; i = " << i << "\n"; }  // warning: 'initializing': conversion from 'double' to 'int', possible loss of data
    //{ int i {3.7}; std::cout << "int i {3.7}; i = " << i << "\n"; }  // error: conversion from 'double' to 'int' requires a narrowing conversion
    { int i{ static_cast<int>(3.7) }; std::cout << "int i {static_cast<int>(3.7)}; i = " << i << "\n"; }
    { int i = { static_cast<int>(3.7) }; std::cout << "int i = { static_cast<int>(3.7) }; i = " << i << "\n"; }  // the = is optional with {}
    { std::vector<int> v{ 1, 2, 3 }; std::cout << "std::vector v{ 1, 2, 3 }; v = " << v << "; type of v = " << typeid(v).name() << "\n"; }  // std::vector<int>
    { std::vector<int> v = { 1, 2, 3 }; std::cout << "std::vector<int> v = { 1, 2, 3 }; v = " << v << "; type of v = " << typeid(v).name() << "\n"; }  // std::vector<int>
}
