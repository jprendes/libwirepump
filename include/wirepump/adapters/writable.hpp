#pragma once

#include <cstdint>
#include <type_traits>
#include <utility>

namespace wirepump {

namespace traits {

template <typename, typename, typename> struct trait;

}

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

namespace adapters {

template <typename Stream>
class writable {
  public:
    static_assert(details::is_writable_v<std::decay_t<Stream>>, "Stream should look like an output stream");

    template<typename... Args>
    writable(Args&&... args)
      : m_stream{std::forward<Args>(args)...}
    {}

    template <typename T>
    void write(T const & v) {
        traits::trait<T, Stream, void>::write(*this, v);
    }
  
  protected:
    Stream m_stream;

    void write_byte(uint8_t byte) {
        m_stream.put(byte);
    }

    friend struct traits::trait<uint8_t, Stream, void>;
};

}

}
