#ifndef __PROBLEMS_H__
#define __PROBLEMS_H__

#include <cassert>
#include <functional>
#include <vector>

#include "Chapter1_MathProblems.h"
#include "Chapter2_LanguageFeatures.h"
#include "Chapter3_StringsAndRegularExpressions.h"
#include "Chapter4_StreamsAndFilesystems.h"
#include "Chapter5_DateAndTime.h"
#include "Chapter6_AlgorithmsAndDataStructures.h"

class Problems
{
    using FunctionType = std::function<void()>;

public:
    static Problems& get_instance()
    {
        static Problems instance;
        return instance;
    }
    constexpr size_t size()
    {
        return data_.size();
    }
    void execute(size_t i)
    {
        assert((i > 0) && (i <= data_.size()));
        std::invoke(data_[i - 1]);
    }

private:
    Problems() {};

    std::vector<FunctionType> data_{
        problem_1_main,  // Math problems
        problem_2_main,
        problem_3_main,
        problem_4_main,
        problem_5_main,
        problem_6_main,
        problem_7_main,
        problem_8_main,
        problem_9_main,
        problem_10_main,
        problem_11_main,
        problem_12_main,
        problem_13_main,
        problem_14_main,

        problem_15_main,  // Language features
        problem_16_main,
        problem_17_main,
        problem_18_main,
        problem_19_main,
        problem_20_main,
        problem_21_main,
        problem_22_main,

        problem_23_main,  // Strings and regular expressions
        problem_24_main,
        problem_25_main,
        problem_26_main,
        problem_27_main,
        problem_28_main,
        problem_29_main,
        problem_30_main,
        problem_31_main,

        problem_32_main,  // Streams and filesystems
        problem_33_main,
        problem_34_main,
        problem_35_main,
        problem_36_main,
        problem_37_main,
        problem_38_main,

        problem_39_main,  // Date and time
        problem_40_main,
        problem_41_main,
        problem_42_main,
        problem_43_main,
        problem_44_main,

        problem_45_main,  // Algorithms and data structures
        problem_46_main,
        problem_47_main,
        problem_48_main,
        problem_49_main,
        problem_50_main,
        problem_51_main,
        problem_52_main,
        problem_53_main,
        problem_54_main,
        problem_55_main,
    };
};

#endif
