#pragma once

#include "wirepump/traits/trait.hpp"
#include "wirepump/traits/byte.hpp"

#include <cstdint>
#include <cstddef>
#include <stdexcept>
#include <type_traits>

namespace wirepump::traits {

template <typename UnsignedInteger, typename Stream>
struct trait<
    UnsignedInteger,
    Stream,
    std::enable_if_t< std::is_integral_v<UnsignedInteger> && std::is_unsigned_v<UnsignedInteger> >
> {
    static UnsignedInteger read(adapters::readable<Stream> & c) {
        UnsignedInteger value = 0;
        uint8_t byte = 0;
        size_t shift = 0;
        do {
            byte = c.template read<uint8_t>();
            UnsignedInteger slice = byte & 0x7F;
            if ((shift >= (8 * sizeof(UnsignedInteger)) && slice != 0) || slice << shift >> shift != slice) {
                throw std::runtime_error("malformed uleb128, extends past end");
            }
            value += slice << shift;
            shift += 7;
        } while (byte & 0x80);
        return value;
    }

    static void write(adapters::writable<Stream> & c, UnsignedInteger const & v) {
        UnsignedInteger value = v;
        do {
            uint8_t byte = value & 0x7f;
            value >>= 7;
            if (value != 0) {
                byte |= 0x80;
            }
            c.write(byte);
        } while (value != 0);
    }
};

}
