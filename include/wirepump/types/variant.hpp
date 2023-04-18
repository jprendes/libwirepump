#pragma once

#include "wirepump/impl.hpp"
#include "wirepump/types/unsigned_integers.hpp"

#include <cstddef>
#include <variant>
#include <stdexcept>

namespace wirepump {

template <typename Stream, typename... Tp>
struct read_impl<Stream, std::variant<Tp...>> {
    static auto read(Stream & c, std::variant<Tp...> & value) -> read_result<Stream> {
        size_t index;
        co_await wirepump::read(c, index);
        co_await read_alternative(c, value, index);
    }

  private:
    template <size_t I = 0>
    static auto read_alternative(Stream & c, std::variant<Tp...> & value, size_t index) -> read_result<Stream> {
        using Variant = std::variant<Tp...>;

        if constexpr(I >= std::variant_size_v<Variant>) {
            throw std::runtime_error{"Variant index " + std::to_string(I + index) + " out of bounds"};
        } else {
            if (index == 0) {
                std::variant_alternative_t<I, Variant> alternative;
                co_await wirepump::read(c, alternative);
                value = Variant{std::in_place_index<I>, std::move(alternative)};
            } else {
                co_await read_alternative<I + 1>(c, value, index - 1);
            }
        }
    }
};

template <typename Stream, typename... Tp>
struct write_impl<Stream, std::variant<Tp...>> {
    static auto write(Stream & c, std::variant<Tp...> const & value) -> write_result<Stream> {
        co_await wirepump::write(c, value.index());
        co_await std::visit([&c](auto const & v) -> write_result<Stream> {
            co_await wirepump::write(c, v);
        }, value);
    }
};

}
