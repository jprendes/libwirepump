#pragma once

#include "wirepump/traits/trait.hpp"

#include "cista/reflection/for_each_field.h"
#include "cista/reflection/to_tuple.h"

#include <type_traits>

namespace wirepump::traits {

template <typename T, typename Stream>
struct trait<
    T,
    Stream,
    std::enable_if_t<cista::to_tuple_works_v<T>>
> {
    static T read(adapters::readable<Stream> & c) {
        T value;
        cista::for_each_field(value, [&c](auto & v) {
            v = c.template read<std::decay_t<decltype(v)>>();
        });
        return value;
    }

    static void write(adapters::writable<Stream> & c, T const & value) {
        cista::for_each_field(value, [&c](auto const & v) {
            c.write(v);
        });
    }
};

}
