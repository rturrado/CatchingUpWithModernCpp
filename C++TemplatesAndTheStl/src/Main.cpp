#include <iostream>

#include "SplitAndReverse.h"
#include "TemplateVariablesWithConstexpr.h"
#include "Transform.h"
#include "TypeInference.h"

int main()
{
    // Split and reverse
    { std::cout << "[SPLIT AND REVERSE]\n"; split_and_reverse_main(); std::cout << "\n"; }
    // Template variables with constexpr
    { std::cout << "[TEMPLATE VARIABLES WITH CONSTEXPR]\n"; template_variables_with_constexpr_main(); std::cout << "\n"; }
    // Transform
    { std::cout << "[TRANSFORM]\n"; transform_main(); std::cout << "\n"; }
    // Type inference
    { std::cout << "[TYPE INFERENCE]\n"; type_inference_main();    std::cout << "\n"; }
}
