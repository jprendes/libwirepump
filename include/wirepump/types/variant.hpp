#pragma once

#include "wirepump/types/traits.hpp"
#include "wirepump/types/unsigned_integers.hpp"

#include <cstddef>
#include <variant>
#include <stdexcept>
#include <type_traits>

namespace wirepump {

namespace details {

template <size_t I = 0, typename Stream, typename... Tp>
auto read_variant_impl(Stream & c, std::variant<Tp...> & value, size_t index) -> traits::read_result<Stream> {
    using Variant = std::variant<Tp...>;

    if constexpr(I >= std::variant_size_v<Variant>) {
        throw std::runtime_error{"Variant index " + std::to_string(I + index) + " out of bounds"};
    } else {
        if (index == 0) {
            std::variant_alternative_t<I, Variant> alternative;
            co_await read(c, alternative);
            value = Variant{std::in_place_index<I>, std::move(alternative)};
        } else {
            co_await read_variant_impl<I + 1>(c, value, index - 1);
        }
    }
}

}

template <typename Stream, typename... Tp>
auto read(Stream & c, std::variant<Tp...> & value) -> traits::read_result<Stream> {
    size_t index;
    co_await read(c, index);
    co_await details::read_variant_impl(c, value, index);
}

template <typename Stream, typename... Tp>
auto write(Stream & c, std::variant<Tp...> const & value) -> traits::write_result<Stream> {
    co_await write(c, value.index());
    co_await std::visit([&c](auto const & v) -> typename traits::write_result<Stream> {
        co_await write(c, v);
    }, value);
}

}
