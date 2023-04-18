#pragma once

#include "wirepump/impl.hpp"
#include "wirepump/types/unsigned_integers.hpp"
#include "wirepump/types/char.hpp"

#include <coroutine>
#include <cstdint>
#include <string_view>
#include <utility>

namespace wirepump {

template <typename Stream>
struct read_impl<Stream, std::string_view> {
    static auto read(Stream & c, std::string_view &) -> read_result<Stream> {
        static_assert(traits::always_false_v<Stream, std::string_view>, "Unimplemented read method. Read to a std::string instead");
        co_return; // dummy co_return so that we have a coroutine
    }
};

template <typename Stream>
struct write_impl<Stream, std::string_view> {
    static auto write(Stream & c, std::string_view const & value) -> write_result<Stream> {
        co_await wirepump::write(c, value.size());
        for (auto const & entry : value) {
            co_await wirepump::write(c, entry);
        }
    }
};

}
