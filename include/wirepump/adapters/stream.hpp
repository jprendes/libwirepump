#pragma once

#include <cstdint>
#include <stdexcept>
#include <concepts>

#include "wirepump/coroutines/sync_task.hpp"
#include "wirepump/impl.hpp"

namespace wirepump {

struct unexpected_eof : std::runtime_error {
    unexpected_eof()
        : std::runtime_error{"Unexpected end of stream"}
    {}
};

template <typename Stream>
    requires requires (Stream stream, char c) {
        stream.get(c);
        { stream.eof() } -> std::same_as<bool>;
    }
struct impl<Stream, uint8_t, READ_IMPL> {
    static auto read(Stream & c, uint8_t & ch) -> coroutines::sync_task<void> {
        ch = c.get();
        if (c.eof()) throw unexpected_eof{};
        co_return;
    }
};

template <typename Stream>
    requires requires (Stream stream, char c) {
        stream.put(c);
    }
struct impl<Stream, uint8_t, WRITE_IMPL> {
    static auto write(Stream & c, uint8_t const & ch) -> coroutines::sync_task<void> {
        c.put(ch);
        co_return;
    }
};

}
