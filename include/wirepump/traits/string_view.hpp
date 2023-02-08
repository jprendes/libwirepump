#pragma once

#include "wirepump/traits/trait.hpp"
#include "wirepump/traits/unsigned_integers.hpp"
#include "wirepump/traits/char.hpp"

#include <cstdint>
#include <string_view>

namespace wirepump::traits {

template <typename Stream>
struct trait<std::string_view, Stream> {

    template <typename T = void>
    static std::string_view read(adapters::readable<Stream> & c) {
        static_assert(always_false_v<T>, "Unimplemented read method. Read to a std::string instead");
        return "";
    }

    static void write(adapters::writable<Stream> & c, std::string_view const & value) {
        c.write(value.size());
        for (auto const & entry : value) {
            c.write(entry);
        }
    }
};

}
