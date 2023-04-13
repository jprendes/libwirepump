#pragma once

#include "wirepump/types/traits.hpp"
#include "wirepump/types/byte.hpp"

#include <cstdint>
#include <cstddef>
#include <stdexcept>
#include <type_traits>

namespace wirepump {

namespace concepts {

template<typename T>
concept UnsignedInteger = std::is_integral_v<T> && std::is_unsigned_v<T>;

}

template <typename Stream, concepts::UnsignedInteger T>
struct impl<Stream, T> {
    static auto read(Stream & c, T & value) -> read_result<Stream> {
        value = 0;
        uint8_t byte = 0;
        size_t shift = 0;
        do {
            co_await impl<Stream, uint8_t>::read(c, byte);
            T slice = byte & 0x7F;
            if ((shift >= (8 * sizeof(T)) && slice != 0) || slice << shift >> shift != slice) {
                throw std::runtime_error("malformed uleb128, extends past end");
            }
            value += slice << shift;
            shift += 7;
        } while (byte & 0x80);
    }

    static auto write(Stream & c, T const & v) -> write_result<Stream> {
        T value = v;
        do {
            uint8_t byte = value & 0x7f;
            value >>= 7;
            if (value != 0) {
                byte |= 0x80;
            }
            co_await impl<Stream, uint8_t>::write(c, byte);
        } while (value != 0);
    }
};

}
