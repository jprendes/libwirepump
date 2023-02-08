#pragma once

#include "wirepump/adapters/readable.hpp"
#include "wirepump/adapters/writable.hpp"
#include "wirepump/traits.hpp"

#include <type_traits>

namespace wirepump {

template <typename T>
struct serialized {
  public:
    T & wrapped;

    serialized(T & value)
      : wrapped(value)
    {}

    template <typename Stream>
    friend
    Stream & operator<<(Stream & stream, serialized const & value) {
        adapters::writable<Stream &>{stream}.write(value.wrapped);
        return stream;
    }

    template <typename Stream>
    friend
    Stream & operator>>(Stream & stream, serialized & value) {
        static_assert(!std::is_const_v<T>, "Can't write to a const value");
        value.wrapped = adapters::readable<Stream &>{stream}.template read<T>();
        return stream;
    }

    template <typename Stream>
    friend
    Stream & operator>>(Stream & stream, serialized && value) {
        static_assert(!std::is_const_v<T>, "Can't write to a const value");
        value.wrapped = adapters::readable<Stream &>{stream}.template read<T>();
        return stream;
    }
};

template<class T>
serialized(T &) -> serialized<T>;

template<class T>
serialized(T const &) -> serialized<T const>;

}
