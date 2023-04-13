#pragma once

#include "wirepump/types/traits.hpp"

#include <cstdint>
#include <utility>

namespace wirepump {

template <typename Stream>
auto read(Stream & c, uint8_t & ch) -> traits::read_result<Stream> {
    co_await traits::readable<Stream>::read_byte(c, ch);
}

template <typename Stream>
auto write(Stream & c, uint8_t const & ch) -> traits::write_result<Stream> {
    co_await traits::writable<Stream>::write_byte(c, ch);
}

}
