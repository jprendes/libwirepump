#pragma once

#include "wirepump/types/traits.hpp"

#include "cista/reflection/to_tuple.h"

namespace wirepump {

template <typename Stream, typename T>
    requires cista::to_tuple_works_v<T>
struct impl<Stream, T> {
    static auto read(Stream & c, T & value) -> read_result<Stream> {
        co_await std::apply([&c]<typename ...Tp>(Tp & ...v) -> read_result<Stream> {
            (..., co_await impl<Stream, Tp>::read(c, v));
        }, cista::to_tuple(value));
    }

    static auto write(Stream & c, T const & value) -> write_result<Stream> {
        co_await std::apply([&c]<typename ...Tp>(Tp const & ...v) -> write_result<Stream> {
            (..., co_await impl<Stream, Tp>::write(c, v));
        }, cista::to_tuple(value));
    }
};

}
