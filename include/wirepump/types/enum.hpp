#pragma once

#include "wirepump/types/traits.hpp"
#include "wirepump/types/signed_integers.hpp"
#include "wirepump/types/unsigned_integers.hpp"

#include <type_traits>

namespace wirepump {

namespace concepts {

template<typename T>
concept EnumType = std::is_enum_v<T>;

}

template <typename Stream, concepts::EnumType T>
auto read(Stream & c, T & v) -> traits::read_result<Stream> {
    co_await read(c, (std::underlying_type_t<T>&)v);
}

template <typename Stream, concepts::EnumType T>
auto write(Stream & c, T const & v) -> traits::write_result<Stream> {
    co_await write(c, (std::underlying_type_t<T>)v);
}

}
