#pragma once

#include "wirepump/types/traits.hpp"

#include <type_traits>
#include <tuple>

namespace wirepump {

template <typename Stream, typename... Args>
auto read(Stream & c, std::tuple<Args...> & value) -> traits::read_result<Stream> {
    co_await std::apply([&c](auto& ...v) -> traits::read_result<Stream> {
        (..., co_await read(c, v));
    }, value);
}

template <typename Stream, typename... Args>
auto write(Stream & c, std::tuple<Args...> const & value) -> traits::write_result<Stream> {
    co_await std::apply([&c](auto& ...v) -> traits::write_result<Stream> {
        (..., co_await write(c, v));
    }, value);
}

}
