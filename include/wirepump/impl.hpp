#pragma once

#include <coroutine>
#include <cstdint>
#include <utility>

#include "wirepump/coroutines/sync_task.hpp"

namespace wirepump {

namespace traits {

template<typename...>
inline constexpr bool always_false_v = false;

}

template <typename Stream, typename T>
struct read_impl {
    static auto read(Stream & stream, T & v) -> coroutines::sync_task<void> {
        if constexpr (std::same_as<uint8_t, T>) {
            static_assert(traits::always_false_v<Stream>, "Unimplemented adapter to read from 'Stream'.");
        } else {
            static_assert(traits::always_false_v<Stream, T>, "Unimplemented deserializer for type 'T'.");
        }
        co_return;
    }
};

template <typename Stream, typename T>
struct write_impl {
    static auto write(Stream & stream, T const & v) -> coroutines::sync_task<void> {
        if constexpr (std::same_as<uint8_t, T>) {
            static_assert(traits::always_false_v<Stream>, "Unimplemented adapter to write to 'Stream'.");
        } else {
            static_assert(traits::always_false_v<Stream, T>, "Unimplemented serializer for type 'T'.");
        }
        co_return;
    }
};

template <typename Stream>
using read_result = decltype(read_impl<Stream, uint8_t>::read(std::declval<Stream &>(), std::declval<uint8_t &>()));

template <typename Stream>
using write_result = decltype(write_impl<Stream, uint8_t>::write(std::declval<Stream &>(), std::declval<uint8_t const &>()));

template <typename Stream, typename T>
auto read(Stream & c, T & v) {
    return read_impl<Stream, T>::read(c, v);
}

template <typename Stream, typename T>
auto write(Stream & c, T const & v) {
    return write_impl<Stream, T>::write(c, v);
}

}