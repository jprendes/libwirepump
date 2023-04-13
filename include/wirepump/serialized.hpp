#pragma once

#include "wirepump/adapters/stream.hpp"
#include "wirepump/types.hpp"

#include <type_traits>

namespace wirepump {

template <typename T>
struct serialized {
  public:
    T & wrapped;

    serialized(T & value)
      : wrapped(value)
    {}

    template <concepts::WritableStream Stream>
    friend
    Stream & operator<<(Stream & stream, serialized const & value) {
        write(stream, value.wrapped);
        return stream;
    }

    template <concepts::ReadableStream Stream>
    friend
    Stream & operator>>(Stream & stream, serialized & value) {
        static_assert(!std::is_const_v<T>, "Can't write to a const value");
        read(stream, value.wrapped);
        return stream;
    }

    template <concepts::ReadableStream Stream>
    friend
    Stream & operator>>(Stream & stream, serialized && value) {
        static_assert(!std::is_const_v<T>, "Can't write to a const value");
        read(stream, value.wrapped);
        return stream;
    }
};

template<class T>
serialized(T &) -> serialized<T>;

template<class T>
serialized(T const &) -> serialized<T const>;

}
