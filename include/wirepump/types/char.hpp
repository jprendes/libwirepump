#pragma once

#include "wirepump/types/traits.hpp"

#include <cstdint>
#include <utility>

namespace wirepump {

template <typename Stream>
auto read(Stream & c, char & ch) -> traits::read_result<Stream> {
    co_await read(c, (uint8_t &)ch);
}

template <typename Stream>
auto write(Stream & c, char const & ch) -> traits::write_result<Stream> {
    co_await write(c, (uint8_t)ch);
}

}
