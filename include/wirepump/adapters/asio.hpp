#pragma once

#include <cstdint>

#include "wirepump/types/traits.hpp"

#if defined __has_include
#  if __has_include (<asio/awaitable.hpp>)
#    define _WIREPUMP_ASIO_AWAITABLE
#  endif
#  if __has_include (<asio/use_awaitable.hpp>)
#    define _WIREPUMP_ASIO_USE_AWAITABLE
#  endif
#  if __has_include (<asio/read.hpp>)
#    define _WIREPUMP_ASIO_READ
#  endif
#  if __has_include (<asio/write.hpp>)
#    define _WIREPUMP_ASIO_WRITE
#  endif
#  if __has_include (<boost/asio/awaitable.hpp>)
#    define _WIREPUMP_BOOST_ASIO_AWAITABLE
#  endif
#  if __has_include (<boost/asio/use_awaitable.hpp>)
#    define _WIREPUMP_BOOST_ASIO_USE_AWAITABLE
#  endif
#  if __has_include (<boost/asio/read.hpp>)
#    define _WIREPUMP_BOOST_ASIO_READ
#  endif
#  if __has_include (<boost/asio/write.hpp>)
#    define _WIREPUMP_BOOST_ASIO_WRITE
#  endif
#endif

#if defined(_WIREPUMP_ASIO_READ) && defined(_WIREPUMP_ASIO_AWAITABLE) && defined(_WIREPUMP_ASIO_USE_AWAITABLE)

# include <asio/awaitable.hpp>
# include <asio/use_awaitable.hpp>
# include <asio/read.hpp>

namespace wirepump {

template <typename Stream>
    requires requires (Stream stream, char c) {
        stream.async_read_some(asio::buffer(&c, 1), asio::use_awaitable);
        asio::async_read(stream, asio::buffer(&c, 1), asio::use_awaitable);
    }
struct impl<Stream, uint8_t, READ_IMPL> {
    static auto read(Stream & stream, uint8_t & ch) -> asio::awaitable<void> {
        co_await asio::async_read(stream, asio::buffer(&ch, 1), asio::use_awaitable);
    }
};

}

#elif defined(_WIREPUMP_BOOST_ASIO_READ) && defined(_WIREPUMP_BOOST_ASIO_AWAITABLE) && defined(_WIREPUMP_BOOST_ASIO_USE_AWAITABLE)

# include <boost/asio/awaitable.hpp>
# include <boost/asio/use_awaitable.hpp>
# include <boost/asio/read.hpp>

namespace wirepump {

template <typename Stream>
    requires requires (Stream stream, char c) {
        stream.async_read_some(boost::asio::buffer(&c, 1), boost::asio::use_awaitable);
        boost::asio::async_read(stream, boost::asio::buffer(&c, 1), boost::asio::use_awaitable);
    }
struct impl<Stream, uint8_t, READ_IMPL> {
    static auto read(Stream & stream, uint8_t & ch) -> boost::asio::awaitable<void> {
        co_await boost::asio::async_read(stream, boost::asio::buffer(&ch, 1), boost::asio::use_awaitable);
    }
};

}

#endif

#if defined(_WIREPUMP_ASIO_WRITE) && defined(_WIREPUMP_ASIO_AWAITABLE) && defined(_WIREPUMP_ASIO_USE_AWAITABLE)

# include <asio/awaitable.hpp>
# include <asio/use_awaitable.hpp>
# include <asio/write.hpp>

namespace wirepump {

template <typename Stream>
    requires requires (Stream stream, char const c) {
        stream.async_write_some(asio::buffer(&c, 1), asio::use_awaitable);
        asio::async_write(stream, asio::buffer(&c, 1), asio::use_awaitable);
    }
struct impl<Stream, uint8_t, WRITE_IMPL> {
    static auto write(Stream & stream, uint8_t const & ch) -> asio::awaitable<void> {
        co_await asio::async_write(stream, asio::buffer(&ch, 1), asio::use_awaitable);
    }
};

}

#elif defined(_WIREPUMP_BOOST_ASIO_WRITE) && defined(_WIREPUMP_BOOST_ASIO_AWAITABLE) && defined(_WIREPUMP_BOOST_ASIO_USE_AWAITABLE)

# include <boost/asio/awaitable.hpp>
# include <boost/asio/use_awaitable.hpp>
# include <boost/asio/write.hpp>

namespace wirepump {

template <typename Stream>
    requires requires (Stream stream, char const c) {
        stream.async_write_some(boost::asio::buffer(&c, 1), boost::asio::use_awaitable);
        boost::asio::async_write(stream, boost::asio::buffer(&c, 1), boost::asio::use_awaitable);
    }
struct impl<Stream, uint8_t, WRITE_IMPL> {
    static auto write(Stream & stream, uint8_t const & ch) -> boost::asio::awaitable<void> {
        co_await boost::asio::async_write(stream, boost::asio::buffer(&ch, 1), boost::asio::use_awaitable);
    }
};

}

#endif
