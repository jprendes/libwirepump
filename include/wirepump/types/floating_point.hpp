#pragma once

#include "wirepump/impl.hpp"

#include <concepts>

namespace wirepump {

template <typename Stream, std::floating_point T>
struct read_impl<Stream, T> {
    static auto read(Stream & c, T & v) -> read_result<Stream> {
        union {
            uint8_t bytes[sizeof(T)];
            T value;
        } value;

        for (auto & byte : value.bytes) {
            co_await wirepump::read(c, byte);
        }

        v = value.value;
    }
};

template <typename Stream, std::floating_point T>
struct write_impl<Stream, T> {
    static auto write(Stream & c, T const & v) -> write_result<Stream> {
        union {
            uint8_t bytes[sizeof(T)];
            T value;
        } value;

        value.value = v;

        for (auto & byte : value.bytes) {
            co_await wirepump::write(c, byte);
        }
    }
};

}
