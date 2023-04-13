#pragma once

#include "wirepump/types/traits.hpp"

#include <tuple>

namespace wirepump {

template <typename Stream, typename... Args>
struct impl<Stream, std::tuple<Args...>> {
    static auto read(Stream & c, std::tuple<Args...> & value) -> read_result<Stream> {
        co_await std::apply([&c]<typename ...Tp>(Tp & ...v) -> read_result<Stream> {
            (..., co_await impl<Stream, Tp>::read(c, v));
        }, value);
    }

    static auto write(Stream & c, std::tuple<Args...> const & value) -> write_result<Stream> {
        co_await std::apply([&c]<typename ...Tp>(Tp const & ...v) -> write_result<Stream> {
            (..., co_await impl<Stream, Tp>::write(c, v));
        }, value);
    }
};

}
