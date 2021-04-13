#include <iostream>
#include <numeric>
#include <string>
#include <vector>

#include "MoveConstructor.h"

/* static */ size_t Vector::temp_copy_index = 0;
/* static */ size_t Vector::temp_move_index = 0;
/* static */ size_t Vector::logging_level = 0;

std::string getIndent()
{
    /*
    std::string ret = "";
    if (Vector::logging_level)
    {
        ret = std::string(Vector::logging_level, '\t');
    }
    return ret;
    */
    std::vector<std::string> v{ Vector::logging_level, "\t" };
    return std::accumulate(v.begin(), v.end(), std::string(""));
}

Vector::Vector(const Vector& rhs)
    : sz{ rhs.sz }, elem{ new double[sz] }, name{ std::string("temp_copy_") + std::to_string(Vector::temp_copy_index++) }
{
    Vector::logging_level++;

    std::cout << getIndent() << "Copy constructor(" << name << "). From: " << rhs.name << "\n";

    for (int i = 0; i < sz; ++i)
    {
        elem[i] = rhs.elem[i];
    }

    Vector::logging_level--;
}

Vector& Vector::operator=(const Vector& rhs)
{
    Vector::logging_level++;

    std::cout << getIndent() << "Copy assignment. From: " << rhs.name << "\n";

    sz = rhs.sz;
    //name = rhs.name;
    double* p = new double[sz];
    for (int i = 0; i < sz; ++i)
    {
        p[i] = rhs.elem[i];
    }
    delete[] elem;
    elem = p;

    Vector::logging_level--;

    return *this;
}

Vector::Vector(Vector&& rhs)
    : sz{ rhs.sz }, elem{ rhs.elem }, name{ std::string("temp_move_") + std::to_string(Vector::temp_move_index++) }
{
    Vector::logging_level++;

    std::cout << getIndent() << "Move constructor(" << name << "). From: " << rhs.name << "\n";

    rhs.sz = 0;
    rhs.elem = nullptr;

    Vector::logging_level--;
}

Vector& Vector::operator=(Vector&& rhs)
{
    Vector::logging_level++;

    std::cout << getIndent() << "Move assignment. From: " << rhs.name << "\n";

    sz = rhs.sz;
    //name = rhs.name;
    elem = rhs.elem;
    rhs.sz = 0;
    rhs.elem = nullptr;

    Vector::logging_level--;

    return *this;
}

double& Vector::operator[](int i)
{
    if (i > sz)
    {
        throw Vector_index_out_of_bounds{};
    }
    return elem[i];
}

const double& Vector::operator[](int i) const
{
    if (i > sz)
    {
        throw Vector_index_out_of_bounds{};
    }
    return elem[i];
}


Vector operator+(const Vector& a, const Vector& b)
{
    Vector::logging_level++;

    std::cout << getIndent() << "operator+(" << a.getName() << ", " << b.getName() << ")\n";

    if (a.size() != b.size())
    {
        throw Vector_size_mismatch{};
    }
    std::cout << getIndent() << "Vector ret{a.size(), 'ret'};\n";
    Vector ret{ a.size(), "ret" };
    for (int i = 0; i != a.size(); ++i)
    {
        ret[i] = a[i] + b[i];
    }
    std::cout << getIndent() << "return ret\n";

    Vector::logging_level--;

    return ret;
}

void f(const Vector& x, const Vector& y, const Vector& z)
{
    Vector::logging_level++;

    std::cout << getIndent() << "f(" << x.getName() << ", " << y.getName() << ", " << z.getName() << ")\n";

    std::cout << getIndent() << "Vector r{'r'};\n";
    Vector r{ "r" };
    std::cout << getIndent() << "r = x + y + z\n";
    r = x + y + z;

    Vector::logging_level--;
}

void move_constructor_main()
{
    std::cout << getIndent() << "Vector x{3, 'x'};\n";
    Vector x{3, "x"};
    std::cout << getIndent() << "Vector y{3, 'y'};\n";
    Vector y{3, "y"};
    std::cout << getIndent() << "Vector z{3, 'z'};\n";
    Vector z{3, "z"};

    for (int i = 0; i < 3; ++i)
    {
        x[i] = y[i] = z[i] = i;
    }

    f(x, y, z);
}