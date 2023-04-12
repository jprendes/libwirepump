#pragma once

#include <cstdint>
#include <stdexcept>
#include <type_traits>
#include <utility>

#include "wirepump/adapters/coroutines/sync_void_awaitable.hpp"

namespace wirepump {

namespace concepts {

namespace details {

template <typename T, typename = void>
struct has_get : public std::false_type {};

template <typename T>
struct has_get<
    T,
    std::void_t<decltype(std::declval<T>().get(std::declval<char &>()))>
> : public std::true_type {};

template <typename T>
static constexpr bool has_get_v = has_get<T>::value;

template <typename T, typename = void>
struct has_eof : public std::false_type {};

template <typename T>
struct has_eof<
    T,
    std::enable_if_t<std::is_same_v<bool, decltype(std::declval<T>().eof())>>
> : public std::true_type {};

template <typename T>
static constexpr bool has_eof_v = has_eof<T>::value;

template <typename T>
static constexpr bool is_readable_v = has_get<T>::value && has_eof<T>::value;

}

template <typename T>
concept ReadableStream = details::is_readable_v<std::decay_t<T>>;

}

struct unexpected_eof : std::runtime_error {
    unexpected_eof()
        : std::runtime_error{"Unexpected end of stream"}
    {}
};

template <concepts::ReadableStream S>
auto read(S & c, uint8_t & ch) -> adapters::coroutines::sync_void_awaitable {
    ch = c.get();
    if (c.eof()) throw unexpected_eof{};
    return {};
}

namespace concepts {

namespace details {

template <typename T, typename = void>
struct has_put : public std::false_type {};

template <typename T>
struct has_put<
    T,
    std::void_t<decltype(std::declval<T>().put(std::declval<char>()))>
> : public std::true_type {};

template <typename T>
static constexpr bool has_put_v = has_put<T>::value;

template <typename T>
static constexpr bool is_writable_v = has_put<T>::value;

}

template <typename T>
concept WritableStream = details::is_writable_v<std::decay_t<T>>;

}

template <concepts::WritableStream S>
auto write(S & c, uint8_t const & ch) -> adapters::coroutines::sync_void_awaitable {
    c.put(ch);
    return {};
}

}
