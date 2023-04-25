#pragma once

#include "wirepump/impl.hpp"
#include "wirepump/types/bool.hpp"
#include "wirepump/types/unsigned_integers.hpp"

#include <cstddef>
#include <optional>
#include <stdexcept>

namespace wirepump {

template <typename Stream, typename T>
struct read_impl<Stream, std::optional<T>> {
    static auto read(Stream & c, std::optional<T> & value) -> read_result<Stream> {
        bool has_option;
        co_await wirepump::read(c, has_option);
        if (has_option) {
            T v;
            co_await wirepump::read(c, v);
            value = std::move(v);
        } else {
            value = std::nullopt;
        }
    }
};

template <typename Stream, typename T>
struct write_impl<Stream, std::optional<T>> {
    static auto write(Stream & c, std::optional<T> const & value) -> write_result<Stream> {
        if (value) {
            co_await wirepump::write(c, true);
            co_await wirepump::write(c, *value);
        } else {
            co_await wirepump::write(c, false);
        }
    }
};

}
