#pragma once

#include "wirepump/impl.hpp"
#include "wirepump/types/unsigned_integers.hpp"

#include <cstddef>
#include <vector>
#include <utility>

namespace wirepump {

template <typename Stream, typename T>
struct read_impl<Stream, std::vector<T>> {
    static auto read(Stream & c, std::vector<T> & value) -> read_result<Stream> {
        size_t size;
        co_await wirepump::read(c, size);
        value.clear();
        value.reserve(size);
        for (size_t i = 0; i < size; ++i) {
            T elem;
            co_await wirepump::read(c, elem);
            value.push_back(std::move(elem));
        }
    }
};

template <typename Stream, typename T>
struct write_impl<Stream, std::vector<T>> {
    static auto write(Stream & c, std::vector<T> const & value) -> write_result<Stream> {
        co_await wirepump::write(c, value.size());
        for (auto const & entry : value) {
            co_await wirepump::write(c, entry);
        }
    }
};

}
