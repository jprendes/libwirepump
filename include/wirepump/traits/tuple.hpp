#pragma once

#include "wirepump/traits/trait.hpp"

#include <type_traits>
#include <tuple>

namespace wirepump::traits {

template <typename... Args, typename Stream>
struct trait<
    std::tuple<Args...>,
    Stream
> {
    static std::tuple<Args...> read(adapters::readable<Stream> & c) {
        std::tuple<Args...> value;
        std::apply([&c](auto& ...v) {
            (..., (v = c.template read<std::decay_t<decltype(v)>>()));
        }, value);
        return value;
    }

    static void write(adapters::writable<Stream> & c, std::tuple<Args...> const & value) {
        std::apply([&c](auto& ...v) {
            (..., c.write(v));
        }, value);
    }
};

}
