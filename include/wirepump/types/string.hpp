#pragma once

#include "wirepump/types/traits.hpp"
#include "wirepump/types/string_view.hpp"
#include "wirepump/types/unsigned_integers.hpp"
#include "wirepump/types/char.hpp"

#include <cstdint>
#include <string>
#include <string_view>

namespace wirepump {

template <typename Stream>
struct impl<Stream, std::string> {
    static auto read(Stream & c, std::string & value) -> read_result<Stream> {
        size_t size;
        char ch;
        co_await impl<Stream, size_t>::read(c, size);
        value.clear();
        value.reserve(size);
        for (size_t i = 0; i < size; ++i) {
            co_await impl<Stream, char>::read(c, ch);
            value.push_back(ch);
        }
    }

    static auto write(Stream & c, std::string const & value) -> write_result<Stream> {
        co_await impl<Stream, std::string_view>::write(c, value);
    }
};

}
