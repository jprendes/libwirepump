#pragma once

#include <cstdint>

#include "wirepump/types/traits.hpp"

#if defined __has_include
#  if __has_include (<asio/awaitable.hpp>)
#    include <asio/awaitable.hpp>
#    define WIREPUMP_ASIO_AWAITABLE
#  endif
#  if __has_include (<asio/use_awaitable.hpp>)
#    include <asio/use_awaitable.hpp>
#    define WIREPUMP_ASIO_USE_AWAITABLE
#  endif
#  if __has_include (<asio/read.hpp>)
#    include <asio/read.hpp>
#    define WIREPUMP_ASIO_READ
#  endif
#  if __has_include (<asio/write.hpp>)
#    include <asio/write.hpp>
#    define WIREPUMP_ASIO_WRITE
#  endif
#endif

#if defined(WIREPUMP_ASIO_AWAITABLE) && defined(WIREPUMP_ASIO_USE_AWAITABLE)

namespace wirepump {

#if defined(WIREPUMP_ASIO_READ)

template <typename Stream>
    requires requires (Stream stream, char c[1]) {
        asio::async_read(stream, asio::buffer((char[1])c), asio::use_awaitable);
    }
struct impl<Stream, uint8_t, READ_IMPL> {
    static auto read(Stream & stream, uint8_t & ch) -> asio::awaitable<void> {
        char data[1];
        co_await asio::async_read(stream, asio::buffer(data), asio::use_awaitable);
        ch = data[0];
    }
};

#endif

#if defined(WIREPUMP_ASIO_WRITE)

template <typename Stream>
    requires requires (Stream stream, char c[1]) {
       asio::async_write(stream, asio::buffer((char[1])c), asio::use_awaitable);
    }
struct impl<Stream, uint8_t, WRITE_IMPL> {
    static auto write(Stream & stream, uint8_t const & ch) -> asio::awaitable<void> {
        char data[1] = { ch };
        co_await asio::async_write(stream, asio::buffer(data), asio::use_awaitable);
    }
};

#endif

}

#endif