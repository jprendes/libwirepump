#pragma once

#include "wirepump/traits/trait.hpp"
#include "wirepump/traits/byte.hpp"

#include <cstdint>

namespace wirepump::traits {

template <typename Stream>
struct trait<char, Stream> {
    static char read(adapters::readable<Stream> & c) {
        return c.template read<uint8_t>();
    }

    static void write(adapters::writable<Stream> & c, char const & v) {
        c.write((uint8_t)v);
    }
};

}
