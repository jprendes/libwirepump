#pragma once

#include "wirepump/types/traits.hpp"
#include "wirepump/types/string_view.hpp"
#include "wirepump/types/unsigned_integers.hpp"
#include "wirepump/types/char.hpp"

#include <cstdint>
#include <string>
#include <string_view>
#include <type_traits>

namespace wirepump {

template <typename Stream>
auto read(Stream & c, std::string & value) -> traits::read_result<Stream> {
    size_t size;
    char ch;
    co_await read(c, size);
    value.clear();
    value.reserve(size);
    for (size_t i = 0; i < size; ++i) {
        co_await read(c, ch);
        value.push_back(ch);
    }
}

template <typename Stream>
auto write(Stream & c, std::string const & value) -> traits::write_result<Stream> {
    co_await write(c, std::string_view{value});
}

}
