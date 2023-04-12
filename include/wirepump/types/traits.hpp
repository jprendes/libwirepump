#pragma once

#include <cstdint>
#include <utility>

namespace wirepump::traits {

template <typename Stream>
using read_result = decltype(read(std::declval<Stream &>(), std::declval<uint8_t &>()));

template <typename Stream>
using write_result = decltype(write(std::declval<Stream &>(), std::declval<uint8_t const &>()));

template <class T>
inline constexpr bool always_false_v = false;

}
