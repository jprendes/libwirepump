#pragma once

#include "wirepump/traits/trait.hpp"
#include "wirepump/traits/unsigned_integers.hpp"

#include <cstddef>
#include <vector>
#include <type_traits>

namespace wirepump::traits {

template <typename T, typename Stream>
struct trait<std::vector<T>, Stream> {
    static std::vector<T> read(adapters::readable<Stream> & c) {
        std::vector<T> value;
        auto size = c.template read<size_t>();
        value.reserve(size);
        for (size_t i = 0; i < size; ++i) {
            value.push_back(c.template read<T>());
        }
        return value;
    }

    static void write(adapters::writable<Stream> & c, std::vector<T> const & value) {
        c.write(value.size());
        for (auto const & entry : value) {
            c.write(entry);
        }
    }
};

}
