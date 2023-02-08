#pragma once

#include "wirepump/traits/trait.hpp"
#include "wirepump/traits/byte.hpp"

#include <type_traits>

namespace wirepump::traits {

template <typename FloatingPointNumber, typename Stream>
struct trait<
    FloatingPointNumber,
    Stream,
    std::enable_if_t< std::is_floating_point_v<FloatingPointNumber> >
> {
    static FloatingPointNumber read(adapters::readable<Stream> & c) {
        union {
            uint8_t bytes[sizeof(FloatingPointNumber)];
            FloatingPointNumber value;
        } value;

        for (auto & byte : value.bytes) {
            byte = c.template read<uint8_t>();
        }

        return value.value;
    }

    static void write(adapters::writable<Stream> & c, FloatingPointNumber const & v) {
        union {
            uint8_t bytes[sizeof(FloatingPointNumber)];
            FloatingPointNumber value;
        } value;

        value.value = v;

        for (auto & byte : value.bytes) {
            c.write(byte);
        }
    }
};

}
