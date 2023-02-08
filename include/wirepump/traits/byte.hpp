#pragma once

#include "wirepump/traits/trait.hpp"

#include <cstdint>

namespace wirepump::traits {

template <typename Stream>
struct trait<uint8_t, Stream> {
    static uint8_t read(adapters::readable<Stream> & c) {
        return c.read_byte();
    }

    static void write(adapters::writable<Stream> & c, uint8_t const & v) {
        c.write_byte(v);
    }
};

}
