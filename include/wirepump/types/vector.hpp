#pragma once

#include "wirepump/types/traits.hpp"
#include "wirepump/types/unsigned_integers.hpp"

#include <cstddef>
#include <vector>
#include <type_traits>

namespace wirepump {

template <typename Stream, typename T>
auto read(Stream & c, std::vector<T> & value) -> traits::read_result<Stream> {
    size_t size;
    co_await read(c, size);
    value.clear();
    value.reserve(size);
    for (size_t i = 0; i < size; ++i) {
        T elem;
        co_await read(c, elem);
        value.push_back(std::move(elem));
    }
}

template <typename Stream, typename T>
auto write(Stream & c, std::vector<T> const & value) -> traits::write_result<Stream> {
    co_await write(c, value.size());
    for (auto const & entry : value) {
        co_await write(c, entry);
    }
}

}
