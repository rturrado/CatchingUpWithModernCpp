#ifndef __MOVE_CONSTRUCTOR_H__
#define __MOVE_CONSTRUCTOR_H__

#include <exception>
#include <iostream>
#include <string>

class Vector_index_out_of_bounds : std::exception {};
class Vector_size_mismatch : std::exception {};

std::string getIndent();
void move_constructor_main();

class Vector
{
public:
    static size_t temp_copy_index;
    static size_t temp_move_index;
    static size_t logging_level;

    Vector() = delete;
    Vector(std::string s) : name{s} { std::cout << getIndent() << "Constructor(" << name << ")\n"; };
    Vector(int i, std::string s) : elem{ new double[i] }, sz{ i }, name{s} { std::cout << getIndent() << "Constructor(" << sz << ", " << name << ")\n"; }
    ~Vector() { std::cout << getIndent() << "Destructor: " << name << "\n"; delete[] elem; sz = 0; }
    Vector(const Vector& rhs);
    Vector& operator=(const Vector& rhs);
    Vector(Vector&& rhs);
    Vector& operator=(Vector&& rhs);

    double& operator[](int i);
    const double& operator[](int i) const;
    int size() const { return sz; }
    const std::string& getName() const { return name; }
private:
    int sz = 0;
    double* elem = nullptr;
    std::string name = "UNDEFINED";
};

#endif
