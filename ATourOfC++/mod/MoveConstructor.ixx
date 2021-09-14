export module MoveConstructor;

import <exception>;
import <iostream>;
import <numeric>;
import <string>;
import <vector>;

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
    Vector(std::string s) : name{ s } { std::cout << getIndent() << "Constructor(" << name << ")\n"; };
    Vector(int i, std::string s) : elem{ new double[i] }, sz{ i }, name{ s } { std::cout << getIndent() << "Constructor(" << sz << ", " << name << ")\n"; }
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

export void move_constructor_main()
{
    std::cout << getIndent() << "Vector x{3, 'x'};\n";
    Vector x{ 3, "x" };
    std::cout << getIndent() << "Vector y{3, 'y'};\n";
    Vector y{ 3, "y" };
    std::cout << getIndent() << "Vector z{3, 'z'};\n";
    Vector z{ 3, "z" };

    for (int i = 0; i < 3; ++i)
    {
        x[i] = y[i] = z[i] = i;
    }

    f(x, y, z);
}
