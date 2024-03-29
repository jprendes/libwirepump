#pragma once

#include "wirepump/impl.hpp"
#include "wirepump/types/string_view.hpp"

#include <coroutine>
#include <cstdint>
#include <string_view>
#include <utility>

namespace wirepump {

template <typename Stream, size_t N>
struct read_impl<Stream, char [N]> {
    using T = char [N];

    static auto read(Stream & c, T &) -> read_result<Stream> {
        static_assert(traits::always_false_v<Stream, char[N]>, "Unimplemented read method. Read to a std::string instead");
        co_await std::suspend_never{}; // dummy co_await do that we have the correct return type
    }
};

template <typename Stream, size_t N>
struct write_impl<Stream, char [N]> {
    using T = char [N];

    static auto write(Stream & c, T const & value) -> write_result<Stream> {
        // Using a char[N] as string literal, it also transmit the '\0'.
        // Reading it as a string, this is usually unexpected and leads to weird behaviour.
        // e.g.,
        //   write(c, "hello");
        //   std::string msg;
        //   read(c, msg);
        //   assert(msg == "hello") // fails, msg.size() is 6, since it includes the '\0'
        // Because of this we disable it
        static_assert(traits::always_false_v<Stream, char[N]>, "Unimplemented write method. Write using a std::string_view instead");
        co_await std::suspend_never{}; // dummy co_await do that we have the correct return type
    }
};

template <typename Stream>
struct read_impl<Stream, char *> {
    using T = char *;

    static auto read(Stream & c, T &) -> read_result<Stream> {
        static_assert(traits::always_false_v<Stream, char *>, "Unimplemented read method. Read to a std::string instead");
        co_await std::suspend_never{}; // dummy co_await do that we have the correct return type
    }
};

template <typename Stream>
struct write_impl<Stream, char *> {
    using T = char *;

    static auto write(Stream & c, T const & value) -> write_result<Stream> {
        co_await wirepump::write(c, std::string_view{value});
    }
};

}
