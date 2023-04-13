#pragma once

#include <cstdint>
#include <utility>

namespace wirepump {

namespace traits {

template <class T>
inline constexpr bool always_false_v = false;

}

inline constexpr int READ_IMPL = 1;
inline constexpr int WRITE_IMPL = 2;

template <typename Stream, typename T, int = 0>
struct impl {
    static auto read(Stream & c, T & v) {
        static_assert(traits::always_false_v<Stream>, "Unimplemented reader");
        return;
    }

    static auto write(Stream & c, T const & v) {
        static_assert(traits::always_false_v<Stream>, "Unimplemented writer");
        return;
    }
};

template <typename Stream>
using read_result = decltype(wirepump::impl<Stream, uint8_t>::read(std::declval<Stream &>(), std::declval<uint8_t &>()));

template <typename Stream>
using write_result = decltype(wirepump::impl<Stream, uint8_t>::write(std::declval<Stream &>(), std::declval<uint8_t const &>()));

template <typename Stream, typename T>
auto read(Stream & c, T & v) {
    return impl<Stream, T>::read(c, v);
}

template <typename Stream, typename T>
auto write(Stream & c, T const & v) {
    return impl<Stream, T>::write(c, v);
}

}