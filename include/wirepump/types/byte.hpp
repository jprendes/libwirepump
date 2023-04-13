#pragma once

#include "wirepump/types/traits.hpp"

#include <cstdint>
#include <utility>

namespace wirepump {

namespace traits {

template <typename Stream, typename = void>
struct is_read_byte_implemented : public std::false_type {};

template <typename Stream>
struct is_read_byte_implemented<
    Stream,
    std::void_t<decltype(impl<Stream, uint8_t, READ_IMPL>::read(std::declval<Stream &>(), std::declval<uint8_t &>()))>
> : public std::true_type {};

template <typename Stream>
static constexpr bool is_read_byte_implemented_v = is_read_byte_implemented<Stream>::value;

template <typename Stream, typename = void>
struct is_write_byte_implemented : public std::false_type {};

template <typename Stream>
struct is_write_byte_implemented<
    Stream,
    std::void_t<decltype(impl<Stream, uint8_t, WRITE_IMPL>::write(std::declval<Stream &>(), std::declval<uint8_t const &>()))>
> : public std::true_type {};

template <typename Stream>
static constexpr bool is_write_byte_implemented_v = is_write_byte_implemented<Stream>::value;

}

template <typename Stream>
struct impl<Stream, uint8_t> {
    static auto read(Stream & c, uint8_t & ch) {
        static_assert(traits::is_read_byte_implemented_v<Stream>, "Unimplemented byte reader");
        return impl<Stream, uint8_t, READ_IMPL>::read(c, ch);
    }

    static auto write(Stream & c, uint8_t const & ch) {
        static_assert(traits::is_write_byte_implemented_v<Stream>, "Unimplemented byte reader");
        return impl<Stream, uint8_t, WRITE_IMPL>::write(c, ch);
    }
};

}
