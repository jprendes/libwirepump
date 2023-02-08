#pragma once

#include "wirepump/traits/trait.hpp"
#include "wirepump/traits/unsigned_integers.hpp"

#include <cstddef>
#include <variant>
#include <stdexcept>
#include <type_traits>

namespace wirepump::traits {

template <typename ...Tp, typename Stream>
struct trait<std::variant<Tp...>, Stream> {
    static std::variant<Tp...> read(adapters::readable<Stream> & c) {
        return read_impl(c, c.template read<size_t>());
    }

    static void write(adapters::writable<Stream> & c, std::variant<Tp...> const & value) {
        c.write(value.index());
        std::visit([&c](auto const & v) {
            c.write(v);
        }, value);
    }
  
  private:
    template <size_t I = 0>
    static std::variant<Tp...> read_impl(adapters::readable<Stream> & c, size_t index) {
        using Variant = std::variant<Tp...>;

        if constexpr(I >= std::variant_size_v<Variant>) {
            throw std::runtime_error{"Variant index " + std::to_string(I + index) + " out of bounds"};
        } else {
            if (index == 0) {
                return Variant{std::in_place_index<I>, c.template read<std::variant_alternative_t<I, Variant>>()};
            }
            return read_impl<I + 1>(c, index - 1);
        }
    }
};

}
