#pragma once

#include "wirepump/types/traits.hpp"

#include <type_traits>

namespace wirepump {

namespace concepts {

template<typename T>
concept FloatingPointNumber = std::is_floating_point_v<T>;

}

template <typename Stream, concepts::FloatingPointNumber T>
auto read(Stream & c, T & v) -> traits::read_result<Stream> {
    union {
        uint8_t bytes[sizeof(T)];
        T value;
    } value;

    for (auto & byte : value.bytes) {
        co_await read(c, byte);
    }

    v = value.value;
}

template <typename Stream, concepts::FloatingPointNumber T>
auto write(Stream & c, T const & v) -> traits::write_result<Stream> {
    union {
        uint8_t bytes[sizeof(T)];
        T value;
    } value;

    value.value = v;

    for (auto & byte : value.bytes) {
        co_await write(c, byte);
    }
}

}
