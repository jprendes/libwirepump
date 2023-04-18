#pragma once

#include "wirepump/impl.hpp"

#include <cstdint>
#include <utility>

namespace wirepump {

template <typename Stream>
struct read_impl<Stream, char> {
    static auto read(Stream & c, char & ch) -> read_result<Stream> {
        co_await wirepump::read(c, (uint8_t &)ch);
    }
};

template <typename Stream>
struct write_impl<Stream, char> {
    static auto write(Stream & c, char const & ch) -> write_result<Stream> {
        co_await wirepump::write(c, (uint8_t)ch);
    }
};

}
