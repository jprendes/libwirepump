#pragma once

#include "wirepump/types/traits.hpp"
#include "wirepump/types/byte.hpp"

#include <type_traits>

namespace wirepump {

namespace concepts {

template<typename T>
concept FloatingPointNumber = std::is_floating_point_v<T>;

}

template <typename Stream, concepts::FloatingPointNumber T>
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
