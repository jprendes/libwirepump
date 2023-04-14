#pragma once

#include "wirepump/types/traits.hpp"

#include <concepts>

namespace wirepump {

template <typename Stream, std::floating_point T>
struct impl<Stream, T> {
    static auto read(Stream & c, T & v) -> read_result<Stream> {
        union {
            uint8_t bytes[sizeof(T)];
            T value;
        } value;

        for (auto & byte : value.bytes) {
            co_await impl<Stream, uint8_t>::read(c, byte);
        }

        v = value.value;
    }

    static auto write(Stream & c, T const & v) -> write_result<Stream> {
        union {
            uint8_t bytes[sizeof(T)];
            T value;
        } value;

        value.value = v;

        for (auto & byte : value.bytes) {
            co_await impl<Stream, uint8_t>::write(c, byte);
        }
    }
};

}
