#pragma once

#include <cstdint>
#include <stdexcept>
#include <type_traits>
#include <utility>

#include "wirepump/adapters/coroutines/sync_void_awaitable.hpp"
#include "wirepump/types/traits.hpp"

namespace wirepump {

namespace concepts {

template<typename T>
concept ReadableStream = requires(T stream, char c) {
    stream.get(c);
    { stream.eof() } -> std::same_as<bool>;
};

template<typename T>
concept WritableStream = requires(T stream, char c) {
    stream.put(c);
};

}

struct unexpected_eof : std::runtime_error {
    unexpected_eof()
        : std::runtime_error{"Unexpected end of stream"}
    {}
};

template <concepts::ReadableStream Stream>
struct impl<Stream, uint8_t, READ_IMPL> {
    static auto read(Stream & c, uint8_t & ch) -> adapters::coroutines::sync_void_awaitable {
        ch = c.get();
        if (c.eof()) throw unexpected_eof{};
        return {};
    }
};

template <concepts::WritableStream Stream>
struct impl<Stream, uint8_t, WRITE_IMPL> {
    static auto write(Stream & c, uint8_t const & ch) -> adapters::coroutines::sync_void_awaitable {
        c.put(ch);
        return {};
    }
};

}
