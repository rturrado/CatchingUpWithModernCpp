#include <exception>
#include <iostream>
#include <string>
#include <vector>

#include "Auto.h"
#include "Bitset.h"
#include "ConditionVariable.h"
#include "Constructors.h"
#include "ConstructorsAndDestructorsOrder.h"
#include "ExplicitConstructor.h"
#include "FileOfDoubles.h"
#include "Filesystem.h"
#include "Initialization.h"
#include "InvalidatedIterators.h"
#include "Istreams.h"
#include "MyClass.h"
#include "MyEnum.h"
#include "MoveConstructor.h"
#include "OstreamsFormatting.h"
#include "PackagedTask.h"
#include "Pair.h"
#include "PointersArraysAndReferences.h"
#include "RawLoopVersusStlAlgorithmPerformance.h"
#include "Span.h"
#include "StreamIterators.h"
#include "StreamIterators2.h"
#include "StringStreams.h"
#include "TemplateArgumentDeduction.h"
#include "TemplateFolds.h"
#include "Thread.h"
#include "Utils.h"
#include "VectorBackInserterPerformance.h"

import Async;
import MyModule;

// Namespaces
namespace MyNamespace
{
    int main() { return 0; }
}
//using MyNamespace::main;  // Error: 'main': function declaration conflicts with 'MyNamespace::main' introduced by using-declaration

int main()
{
/*
    // Auto
    { std::cout << "[AUTO]\n"; auto_main(); std::cout << "\n"; }
*/
    // Async
    { std::cout << "[ASYNC]\n"; async_main(); std::cout << "\n"; }
/*
    // Bitset
    { std::cout << "[BITSET]\n"; bitset_main(); std::cout << "\n"; }
    // Classes
    {
        std::cout << "[CLASSES]\n";
        MyClass myObject;
        std::cout << "size = " << myObject.size() << "\n";
        MyClass myObject2{ 3 };
        std::cout << "size = " << myObject2.size() << "\n";
        std::cout << "\n";
    }
    // Condition variable
    { std::cout << "[CONDITION VARIABLE]\n"; condition_variable_main(); std::cout << "\n"; }
    // Constructors
    { std::cout << "[CONSTRUCTORS]\n"; constructors_main(); std::cout << "\n"; }
    // Constructors and destructors order
    { std::cout << "[CONSTRUCTORS AND DESTRUCTORS ORDER]\n"; cado_main(); std::cout << "\n"; }
    // Enums
    {
        std::cout << "[ENUMS]\n";
        Color myColor{ 7 };
        std::cout << "color = " << color_to_str(myColor) << "\n";
        myColor = Color::yellow;
        std::cout << "color index for yellow = " << static_cast<int>(myColor) << "\n";
        std::cout << "\n";
    }
    // Explicit constructor
    { std::cout << "[EXPLICIT CONSTRUCTOR]\n"; explicit_constructor_main(); std::cout << "\n"; }
    // File of doubles
    {
        std::cout << "[FILE OF DOUBLES]\n";
        try
        {
            file_of_doubles_main();
        }
        catch (const std::exception&)
        {
            std::cout << "File of doubles failed\n";
        }
        std::cout << "\n";
    }
    // Filesystem
    { std::cout << "[FILESYSTEM]\n"; filesystem_main(); std::cout << "\n"; }
    // Initialization
    { std::cout << "[INITIALIZATON]\n"; initialization_main(); std::cout << "\n"; }
    // Input streams
    {
        std::cout << "[INPUT STREAMS]\n";
        std::vector<std::string> v{ read_vector_of_strings_from_istream(std::cin) };  // move constructor
        std::cout << "List of strings = " << v << "\n";
        std::cout << "\n";
    }
    // Invalidated iterators
    { std::cout << "[INVALIDATED ITERATORS]\n"; invalidated_iterators_main(); std::cout << "\n"; }
    // Istreams
    { std::cout << "[ISTREAMS]\n"; istreams_main(); std::cout << "\n"; }
    // Modules
    {
        std::cout << "[MODULES]\n";
        MyModuleClass myModuleObject;
        std::cout << "myModuleObject.getId() = " << myModuleObject.getId() << "\n";
        std::cout << "\n";
    }
    // Move constructor
    { std::cout << "[MOVE CONSTRUCTOR]\n"; move_constructor_main(); std::cout << "\n"; }
    // Ostreams formatting
    { std::cout << "[OSTREAMS FORMATTING]\n"; ostreams_formatting_main(); std::cout << "\n"; }
    // Packaged task
    { std::cout << "[PACKAGED TASK]\n"; packaged_task_main(); std::cout << "\n"; }
    // Pair
    { std::cout << "[PAIR]\n"; pair_main(); std::cout << "\n"; }
    // Pointers, arrays, and references
    { std::cout << "[POINTERS, ARRAYS, AND REFERENCES]\n"; paar_main(); std::cout << "\n"; }
    // Raw loop versus STL algorithm performance
    { std::cout << "[RAW LOOP VERSUS STL ALGORITHM PERFORMANCE]\n"; raw_loop_versus_stl_algorithm_performance_main(); }
    // Span
    { std::cout << "[SPAN]\n"; span_main(); std::cout << "\n"; }
    // Stream iterators
    { std::cout << "[STREAM ITERATORS]\n"; stream_iterators_main(); std::cout << "\n"; }
    { std::cout << "[STREAM ITERATORS 2]\n"; stream_iterators_2_main(); std::cout << "\n"; }
    // String streams
    { std::cout << "[STRING STREAMS]\n"; string_streams_main(); std::cout << "\n"; }
    // Template argument deduction
    { std::cout << "[TEMPLATE ARGUMENT DEDUCTION]\n"; template_argument_deduction_main(); std::cout << "\n"; }
    // Template folds
    { std::cout << "[TEMPLATE FOLDS]\n"; template_folds_main(); std::cout << "\n"; }
    // Thread
    { std::cout << "[THREAD]\n"; thread_main(); std::cout << "\n"; }
    // Vector back inserter performance
    { std::cout << "[VECTOR BACK INSERTER PERFORMANCE]\n"; vector_back_inserter_performance_main(); std::cout << "\n"; \}
*/
    // 
    { /* std::cout << "[]\n"; _main(); std::cout << "\n"; */ }
}
