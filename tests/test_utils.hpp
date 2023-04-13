#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <cxxabi.h>
#include <wirepump.hpp>

template <typename T>
inline std::string type_name() {
    int status;
    return abi::__cxa_demangle(typeid(T).name(), NULL, NULL, &status);
}

inline void assert_impl(const char* expr_str, bool expr, const char* file, const char* function, int line, std::string msg)
{
    if (!expr)
    {
        std::cerr
            << "\x1b[31m"
            << "Assert failed: " << msg << "\n"
            << "\x1b[0m"
            << "  Expected: " << expr_str << "\n"
            << "  Source: " << file << "(l." << line << ") " << function <<"\n";
        std::abort();
    }
}

#if defined(assert)
#undef assert
#endif

#define assert(expr, msg) assert_impl(#expr, expr, __FILE__, __func__, __LINE__, msg)

template <typename T>
T round_trip(T const & original) {
    T copy;
    std::stringstream ss;
    ss << wirepump::serialized(original);
    ss >> wirepump::serialized(copy);
    return copy;
}

template <typename T>
size_t serialized_size(T const & value) {
    std::stringstream ss;
    ss << wirepump::serialized(value);
    return ss.str().size();
}

#define assert_round_trip(T, value) \
    do { \
        T original = value; \
        assert(original == round_trip<T>(original), "Value should be unchanged after a round-trip [" #T "]"); \
    } while (0)

#define assert_size(T, value, expected) \
    do { \
        T original = value; \
        assert(serialized_size<T>(value) == expected, "Serialized size should be " #expected); \
    } while (0)
