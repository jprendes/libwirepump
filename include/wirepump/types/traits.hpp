#pragma once

#include <cstdint>
#include <utility>

namespace wirepump::traits {

template <class T>
inline constexpr bool always_false_v = false;

template <typename Stream>
struct readable {
    static auto read_byte(Stream & c, uint8_t & ch) -> void {
        static_assert(traits::always_false_v<Stream>, "Unimplemented byte reader");
        return;
    }
};

template <typename Stream>
struct writable {
    static auto write_byte(Stream & c, uint8_t const & ch) -> void {
        static_assert(traits::always_false_v<Stream>, "Unimplemented byte writer");
        return;
    }
};

template <typename Stream>
using read_result = decltype(wirepump::traits::readable<Stream>::read_byte(std::declval<Stream &>(), std::declval<uint8_t &>()));

template <typename Stream>
using write_result = decltype(wirepump::traits::writable<Stream>::write_byte(std::declval<Stream &>(), std::declval<uint8_t const &>()));

}
