#pragma once

#include "wirepump/types/traits.hpp"

#include "cista/reflection/for_each_field.h"
#include "cista/reflection/to_tuple.h"

#include <type_traits>

namespace wirepump {

namespace concepts {

template<typename T>
concept TupleLike = cista::to_tuple_works_v<T>;

}

template <typename Stream, concepts::TupleLike T>
auto read(Stream & c, T & value) -> traits::read_result<Stream> {
    co_await std::apply([&c](auto& ...v) -> traits::read_result<Stream> {
        (..., co_await read(c, v));
    }, cista::to_tuple(value));
}

template <typename Stream, concepts::TupleLike T>
auto write(Stream & c, T const & value) -> traits::write_result<Stream> {
    co_await std::apply([&c](auto& ...v) -> traits::write_result<Stream> {
        (..., co_await write(c, v));
    }, cista::to_tuple(value));
}

}
