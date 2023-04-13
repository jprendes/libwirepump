#pragma once

#include "wirepump/types/traits.hpp"

#include <cstdint>
#include <utility>

namespace wirepump {

template <typename Stream>
struct impl<Stream, uint8_t> {
    static auto read(Stream & c, uint8_t & ch) -> read_result<Stream> {
        co_await traits::readable<Stream>::read_byte(c, ch);
    }

    static auto write(Stream & c, uint8_t const & ch) -> write_result<Stream> {
        co_await traits::writable<Stream>::write_byte(c, ch);
    }
};

}
