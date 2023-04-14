#pragma once

#include "wirepump/types/traits.hpp"

#include <cstdint>
#include <utility>

namespace wirepump {

template <typename Stream>
struct impl<Stream, char> {
    static auto read(Stream & c, char & ch) -> read_result<Stream> {
        co_await impl<Stream, uint8_t>::read(c, (uint8_t &)ch);
    }

    static auto write(Stream & c, char const & ch) -> write_result<Stream> {
        co_await impl<Stream, uint8_t>::write(c, ch);
    }
};

}
