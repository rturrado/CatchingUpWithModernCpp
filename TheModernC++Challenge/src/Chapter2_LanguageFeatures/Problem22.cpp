#include "Chapter2_LanguageFeatures.h"
#include "temperature_v1.h"
#include "temperature_v2.h"


void test_temperature_v1()
{
    using namespace my_temperature_v1;
    using namespace my_temperature_v1::literals;

    std::cout << "Using my_temperature_v1:\n";

    std::cout << "\t" << 35.5_deg << " in Fahrenheit: " << to_fahrenheit(35.5_deg) << "\n";
    std::cout << "\t" << 35.5_deg << " in Kelvin: " << to_kelvin(35.5_deg) << "\n\n";

    temperature t1{ 12.3, Scale::Celsius };
    temperature t2{ 12.3, Scale::Fahrenheit };
    temperature t3{ 12.3, Scale::Kelvin };

    std::cout << "\t" << t1 << " == " << t2 << "? " << std::boolalpha << (t1 == t2) << ". ";
    std::cout << t2 << " == " << to_celsius(t2) << " Celsius" << "\n";
    std::cout << "\t" << t1 << " < " << t2 << "? " << std::boolalpha << (t1 < t2) << ". ";
    std::cout << t2 << " == " << to_celsius(t2) << " Celsius" << "\n";
    std::cout << "\t" << t1 << " > " << t3 << "? " << std::boolalpha << (t1 > t3) << ". ";
    std::cout << t3 << " == " << to_celsius(t3) << " Celsius" << "\n\n";

    std::cout << "\t" << t1 << " + " << t2 << " = " << (t1 + t2) << ". ";
    std::cout << t2 << " == " << to_celsius(t2) << " Celsius" << "\n";
    std::cout << "\t" << t1 << " - " << t3 << " = " << (t1 - t3) << ". ";
    std::cout << t3 << " == " << to_celsius(t3) << " Celsius" << "\n\n";
}


void test_temperature_v2()
{
    using namespace my_temperature_v2;
    using namespace my_temperature_v2::literals;

    std::cout << "Using my_temperature_v2:\n";

    std::cout << "\t" << 35.5_deg << " in Fahrenheit: " << temperature_cast<long double, Scale::Fahrenheit>(35.5_deg) << "\n";
    std::cout << "\t" << 35.5_deg << " in Kelvin: " << temperature_cast<long double, Scale::Kelvin>(35.5_deg) << "\n\n";

    temperature<float, Scale::Celsius> t1{ static_cast<float>(12.3) };
    temperature<float, Scale::Fahrenheit> t2{ static_cast<float>(12.3) };
    temperature<float, Scale::Kelvin> t3{ static_cast<float>(12.3) };

    // Now, we can only compare temperatures on the same scale
    std::cout << "\t" << t1 << " == " << t2 << "? " << std::boolalpha << (t1 == temperature_cast<float, Scale::Celsius>(t2)) << ". ";
    std::cout << t2 << " == " << temperature_cast<float, Scale::Celsius>(t2) << "\n";
    std::cout << "\t" << t1 << " < " << t2 << "? " << std::boolalpha << (t1 < temperature_cast<float, Scale::Celsius>(t2)) << ". ";
    std::cout << t2 << " == " << temperature_cast<float, Scale::Celsius>(t2) << "\n";
    std::cout << "\t" << t1 << " > " << t3 << "? " << std::boolalpha << (t1 > temperature_cast<float, Scale::Celsius>(t3)) << ". ";
    std::cout << t3 << " == " << temperature_cast<float, Scale::Celsius>(t3) << "\n\n";

    // Same for arithmetic operations
    std::cout << "\t" << t1 << " + " << t2 << " = " << (t1 + temperature_cast<float, Scale::Celsius>(t2)) << ". ";
    std::cout << t2 << " == " << temperature_cast<float, Scale::Celsius>(t2) << "\n";
    std::cout << "\t" << t1 << " - " << t3 << " = " << (t1 - temperature_cast<float, Scale::Celsius>(t3)) << ". ";
    std::cout << t3 << " == " << temperature_cast<float, Scale::Celsius>(t3) << "\n\n";
}


// Literals of various temperature scales
// Write a small library that enables expressing temperatures in the three most used scales,
// Celsius, Fahrenheit, and Kelvin, and converting between them.
// The library must enable you to write temperature literals in all these scales,
// such as 36.5_deg for Celsius, 97.7_f for Fahrenheit, and 309.65_K for Kelvin;
// perform operations with these values; and convert between them
void problem_22_main()
{
    test_temperature_v1();
    test_temperature_v2();
}
