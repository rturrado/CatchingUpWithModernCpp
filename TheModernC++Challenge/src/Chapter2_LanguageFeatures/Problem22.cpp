#include "Chapter2_LanguageFeatures.h"
#include "temperature.h"

// Literals of various temperature scales
// Write a small library that enables expressing temperatures in the three most used scales,
// Celsius, Fahrenheit, and Kelvin, and converting between them.
// The library must enable you to write temperature literals in all these scales,
// such as 36.5_deg for Celsius, 97.7_f for Fahrenheit, and 309.65_K for Kelvin;
// perform operations with these values; and convert between them
void problem_22_main()
{
    using namespace my_temperature;
    using namespace my_temperature_literals;

    temperature t1{ 35, Scale::Celsius };
    temperature t2{ 35, Scale::Fahrenheit };
    temperature t3{ 35, Scale::Kelvin };

    std::cout << 35.5_deg << " in Fahrenheit: " << to_fahrenheit(35.5_deg) << "\n";
    std::cout << 35.5_deg << " in Kelvin: " << to_kelvin(35.5_deg) << "\n";
}
