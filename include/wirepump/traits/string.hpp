#pragma once

#include "wirepump/traits/trait.hpp"
#include "wirepump/traits/string_view.hpp"
#include "wirepump/traits/unsigned_integers.hpp"
#include "wirepump/traits/char.hpp"

#include <cstdint>
#include <string>
#include <string_view>
#include <type_traits>

namespace wirepump::traits {

template <typename Stream>
struct trait<std::string, Stream> {
    static std::string read(adapters::readable<Stream> & c) {
        std::string value;
        auto size = c.template read<size_t>();
        value.reserve(size);
        for (size_t i = 0; i < size; ++i) {
            value.push_back(c.template read<char>());
        }
        return value;
    }

    static void write(adapters::writable<Stream> & c, std::string const & value) {
        c.write(std::string_view{value});
    }
};

}
