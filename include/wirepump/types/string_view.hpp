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
auto read(Stream & c, std::string_view &) -> traits::read_result<Stream> {
    static_assert(traits::always_false_v<Stream>, "Unimplemented read method. Read to a std::string instead");
    co_await std::suspend_never{}; // dummy co_await do that we have the correct return type
}

template <typename Stream>
auto write(Stream & c, std::string_view const & value) -> traits::write_result<Stream> {
    co_await write(c, value.size());
    for (auto const & entry : value) {
        co_await write(c, entry);
    }
}

}
