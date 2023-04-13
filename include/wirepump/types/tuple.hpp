#pragma once

#include "wirepump/types/traits.hpp"

#include <type_traits>
#include <tuple>

namespace wirepump {

template <typename Stream, typename... Args>
struct impl<Stream, std::tuple<Args...>> {
    static auto read(Stream & c, std::tuple<Args...> & value) -> read_result<Stream> {
        co_await std::apply([&c](auto& ...v) -> read_result<Stream> {
            (..., co_await impl<Stream, std::remove_cvref_t<decltype(v)>>::read(c, v));
        }, value);
    }

    static auto write(Stream & c, std::tuple<Args...> const & value) -> write_result<Stream> {
        co_await std::apply([&c](auto const & ...v) -> write_result<Stream> {
            (..., co_await impl<Stream, std::remove_cvref_t<decltype(v)>>::write(c, v));
        }, value);
    }
};

}
