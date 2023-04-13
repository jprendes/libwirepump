#pragma once

#include <cstdint>
#include <stdexcept>
#include <concepts>

#include "wirepump/adapters/coroutines/sync_void_awaitable.hpp"
#include "wirepump/types/traits.hpp"

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
    static auto read(Stream & c, uint8_t & ch) -> adapters::coroutines::sync_void_awaitable {
        ch = c.get();
        if (c.eof()) throw unexpected_eof{};
        return {};
    }
};

template <typename Stream>
    requires requires (Stream stream, char c) {
        stream.put(c);
    }
struct impl<Stream, uint8_t, WRITE_IMPL> {
    static auto write(Stream & c, uint8_t const & ch) -> adapters::coroutines::sync_void_awaitable {
        c.put(ch);
        return {};
    }
};

}
