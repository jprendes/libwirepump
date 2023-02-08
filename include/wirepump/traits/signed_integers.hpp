#pragma once

#include "wirepump/traits/trait.hpp"
#include "wirepump/traits/byte.hpp"

#include <cstdint>
#include <cstddef>
#include <stdexcept>
#include <type_traits>

namespace wirepump::traits {

template <typename SignedInteger, typename Stream>
struct trait<
    SignedInteger,
    Stream,
    std::enable_if_t< std::is_integral_v<SignedInteger> && std::is_signed_v<SignedInteger> >
> {
    static SignedInteger read(adapters::readable<Stream> & c) {
        using UnsignedInteger = std::make_unsigned_t<SignedInteger>;
        SignedInteger value = 0;
        uint8_t byte = 0;
        size_t shift = 0;
        do {
            byte = c.template read<uint8_t>();
            UnsignedInteger Slice = byte & 0x7f;
            if ((shift >= (8 * sizeof(SignedInteger)) && Slice != (value < 0 ? 0x7f : 0x00)) ||
                (shift == (8 * sizeof(SignedInteger) - 1) && Slice != 0 && Slice != 0x7f)) {
                    throw std::runtime_error("malformed sleb128, extends past end");
            }
            value |= Slice << shift;
            shift += 7;
        } while (byte & 0x80);
        // Sign extend negative numbers if needed.
        if (shift < (8 * sizeof(SignedInteger)) && (byte & 0x40)) {
            value |= (~UnsignedInteger{0}) << shift;
        }
        return value;
    }

    static void write(adapters::writable<Stream> & c, SignedInteger const & v) {
        SignedInteger value = v;
        bool more;
        do {
            uint8_t Byte = value & 0x7f;
            // NOTE: this assumes that this signed shift is an arithmetic right shift.
            value >>= 7;
            more = !((((value == 0 ) && ((Byte & 0x40) == 0)) ||
                    ((value == -1) && ((Byte & 0x40) != 0))));
            if (more) {
                Byte |= 0x80; // Mark this byte to show that more bytes will follow.
            }
            c.write(Byte);
        } while (more);
    }
};

}
