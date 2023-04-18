#pragma once

#include "wirepump/impl.hpp"

#include "cista/reflection/to_tuple.h"

namespace wirepump {

template <typename Stream, typename T>
    requires cista::to_tuple_works_v<T>
struct read_impl<Stream, T> {
    static auto read(Stream & c, T & value) -> read_result<Stream> {
        co_await std::apply([&c]<typename ...Tp>(Tp & ...v) -> read_result<Stream> {
            (..., co_await wirepump::read(c, v));
        }, cista::to_tuple(value));
    }
};

template <typename Stream, typename T>
    requires cista::to_tuple_works_v<T>
struct write_impl<Stream, T> {
    static auto write(Stream & c, T const & value) -> write_result<Stream> {
        co_await std::apply([&c]<typename ...Tp>(Tp const & ...v) -> write_result<Stream> {
            (..., co_await wirepump::write(c, v));
        }, cista::to_tuple(value));
    }
};

}
