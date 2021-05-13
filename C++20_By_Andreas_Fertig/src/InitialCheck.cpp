#include <cstdio>

//#ifdef __cplusplus
//#define CPP_STD __cplusplus
//#elif defined(_MSVC_LANG)
#ifdef _MSVC_LANG
#define CPP_STD _MSVC_LANG
#else
#error("unknown compiler")
#endif

#if defined(_MSC_VER)
#define not !
#endif

#define REQUIRED 202002L

static bool Check(const char* std, unsigned long value)
{
    const static unsigned long STD = CPP_STD;

    printf(" - C++%s: ", std);

    if (STD >= value) {
        printf(" [OK]\n");
    }
    else {
        if (REQUIRED >= value) {
            printf(" [!!!FAILED!!!]\n");
            return false;

        }
        else {
            printf(" [FAILED]\n");
        }
    }

    return true;
}

// VS2019 still doesn't say they support C++20
// even when we compile with C++ Language Standard = /std=c++latest
int initial_check_main()
{
    printf("Supported:\n");

    const bool failed =
        not Check("11", 201103L) || not Check("14", 201402L) || not Check("17", 201703L) || not Check("20", 202002L);

    printf("\nOverall: %s\n", failed ? "UNSUPPORTED" : "READY");

    return failed ? 1 : 0;
}
