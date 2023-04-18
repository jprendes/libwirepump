#pragma once

#include "wirepump/impl.hpp"
#include "wirepump/types/signed_integers.hpp"
#include "wirepump/types/unsigned_integers.hpp"

#include <type_traits>

namespace wirepump {

template <typename Stream, typename T>
    requires std::is_enum_v<T>
struct read_impl<Stream, T> {
    static auto read(Stream & c, T & v) -> read_result<Stream> {
        co_await wirepump::read(c, (std::underlying_type_t<T>&)v);
    }
};

template <typename Stream, typename T>
    requires std::is_enum_v<T>
struct write_impl<Stream, T> {
    static auto write(Stream & c, T const & v) -> write_result<Stream> {
        co_await wirepump::write(c, (std::underlying_type_t<T>)v);
    }
};

}
