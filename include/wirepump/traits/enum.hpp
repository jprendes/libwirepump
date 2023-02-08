#pragma once

#include "wirepump/traits/trait.hpp"
#include "wirepump/traits/signed_integers.hpp"
#include "wirepump/traits/unsigned_integers.hpp"

#include <type_traits>

namespace wirepump::traits {

template <typename EnumType, typename Stream>
struct trait<
    EnumType,
    Stream,
    std::enable_if_t< std::is_enum_v<EnumType> >
> {
    static EnumType read(adapters::readable<Stream> & c) {
        return static_cast<EnumType>(c.template read<std::underlying_type_t<EnumType>>());
    }

    static void write(adapters::writable<Stream> & c, EnumType const & v) {
        c.write(static_cast<std::underlying_type_t<EnumType>>(v));
    }
};

}
