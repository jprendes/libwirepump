#pragma once

#include "wirepump/types/traits.hpp"
#include "wirepump/types/unsigned_integers.hpp"
#include "wirepump/types/char.hpp"

#include <coroutine>
#include <cstdint>
#include <string_view>
#include <utility>

namespace wirepump {

template <typename Stream>
struct impl<Stream, std::string_view> {
    static auto read(Stream & c, std::string_view &) -> read_result<Stream> {
        static_assert(requires { requires false; }, "Unimplemented read method. Read to a std::string instead");
        co_await std::suspend_never{}; // dummy co_await do that we have the correct return type
    }

    static auto write(Stream & c, std::string_view const & value) -> write_result<Stream> {
        co_await impl<Stream, size_t>::write(c, value.size());
        for (auto const & entry : value) {
            co_await impl<Stream, char>::write(c, entry);
        }
    }
};

}
