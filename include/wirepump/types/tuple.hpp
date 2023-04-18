#pragma once

#include "wirepump/impl.hpp"

#include <tuple>

namespace wirepump {

template <typename Stream, typename... Args>
struct read_impl<Stream, std::tuple<Args...>> {
    static auto read(Stream & c, std::tuple<Args...> & value) -> read_result<Stream> {
        co_await std::apply([&c](auto & ...v) -> read_result<Stream> {
            (..., co_await wirepump::read(c, v));
        }, value);
    }
};

template <typename Stream, typename... Args>
struct write_impl<Stream, std::tuple<Args...>> {
    static auto write(Stream & c, std::tuple<Args...> const & value) -> write_result<Stream> {
        co_await std::apply([&c](auto const & ...v) -> write_result<Stream> {
            (..., co_await wirepump::write(c, v));
        }, value);
    }
};

}
