#pragma once

#include "wirepump/types/traits.hpp"
#include "wirepump/types/byte.hpp"

#include <cstdint>
#include <cstddef>
#include <stdexcept>
#include <type_traits>
#include <concepts>

namespace wirepump {

template <typename Stream, std::signed_integral T>
struct impl<Stream, T> {
    static auto read(Stream & c, T & value) -> read_result<Stream> {
        using U = std::make_unsigned_t<T>;
        value = 0;
        uint8_t byte = 0;
        size_t shift = 0;
        do {
            co_await impl<Stream, uint8_t>::read(c, byte);
            U Slice = byte & 0x7f;
            if ((shift >= (8 * sizeof(T)) && Slice != (value < 0 ? 0x7f : 0x00)) ||
                (shift == (8 * sizeof(T) - 1) && Slice != 0 && Slice != 0x7f)) {
                    throw std::runtime_error("malformed sleb128, extends past end");
            }
            value |= Slice << shift;
            shift += 7;
        } while (byte & 0x80);
        // Sign extend negative numbers if needed.
        if (shift < (8 * sizeof(T)) && (byte & 0x40)) {
            value |= (~U{0}) << shift;
        }
    }

    static auto write(Stream & c, T const & v) -> write_result<Stream> {
        T value = v;
        bool more;
        do {
            uint8_t byte = value & 0x7f;
            // NOTE: this assumes that this signed shift is an arithmetic right shift.
            value >>= 7;
            more = !((((value == 0 ) && ((byte & 0x40) == 0)) ||
                    ((value == -1) && ((byte & 0x40) != 0))));
            if (more) {
                byte |= 0x80; // Mark this byte to show that more bytes will follow.
            }
            co_await impl<Stream, uint8_t>::write(c, byte);
        } while (more);
    }
};

}
