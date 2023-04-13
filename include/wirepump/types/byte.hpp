#pragma once

#include "wirepump/types/traits.hpp"

#include <cstdint>
#include <utility>

namespace wirepump {

template <typename Stream>
struct impl<Stream, uint8_t> {
    static auto read(Stream & c, uint8_t & ch) {
        static_assert(requires (Stream stream, uint8_t c) {
            impl<Stream, uint8_t, READ_IMPL>::read(stream, c);
        }, "Unimplemented byte reader");
        return impl<Stream, uint8_t, READ_IMPL>::read(c, ch);
    }

    static auto write(Stream & c, uint8_t const & ch) {
        static_assert(requires (Stream stream, uint8_t c) {
            impl<Stream, uint8_t, WRITE_IMPL>::write(stream, c);
        }, "Unimplemented byte reader");
        return impl<Stream, uint8_t, WRITE_IMPL>::write(c, ch);
    }
};

}
