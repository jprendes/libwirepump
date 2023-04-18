#pragma once

#include "wirepump/impl.hpp"
#include "wirepump/types/string_view.hpp"
#include "wirepump/types/unsigned_integers.hpp"
#include "wirepump/types/char.hpp"

#include <cstdint>
#include <string>
#include <string_view>

namespace wirepump {

template <typename Stream>
struct read_impl<Stream, std::string> {
    static auto read(Stream & c, std::string & value) -> read_result<Stream> {
        size_t size;
        char ch;
        co_await wirepump::read(c, size);
        value.clear();
        value.reserve(size);
        for (size_t i = 0; i < size; ++i) {
            co_await wirepump::read(c, ch);
            value.push_back(ch);
        }
    }
};

template <typename Stream>
struct write_impl<Stream, std::string> {
    static auto write(Stream & c, std::string const & value) -> write_result<Stream> {
        co_await wirepump::write(c, std::string_view{value});
    }
};

}
