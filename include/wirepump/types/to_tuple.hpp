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
struct impl<Stream, T> {
    static auto read(Stream & c, T & value) -> read_result<Stream> {
        co_await std::apply([&c](auto& ...v) -> read_result<Stream> {
            (..., co_await impl<Stream, std::remove_cvref_t<decltype(v)>>::read(c, v));
        }, cista::to_tuple(value));
    }

    static auto write(Stream & c, T const & value) -> write_result<Stream> {
        co_await std::apply([&c](auto const & ...v) -> write_result<Stream> {
            (..., co_await impl<Stream, std::remove_cvref_t<decltype(v)>>::write(c, v));
        }, cista::to_tuple(value));
    }
};

}
