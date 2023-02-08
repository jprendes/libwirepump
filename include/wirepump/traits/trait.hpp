#pragma once

#include "wirepump/adapters/readable.hpp"
#include "wirepump/adapters/writable.hpp"

namespace wirepump::traits {

template <class T>
inline constexpr bool always_false_v = false;

template <typename T, typename Stream, typename = void>
struct trait {
    static T read(adapters::readable<Stream> & c) {
        static_assert(always_false_v<T>, "Unimplemented read method");
    }

    static void write(adapters::writable<Stream> & c, T const & v) {
        static_assert(always_false_v<T>, "Unimplemented write method");
    }
};

}
