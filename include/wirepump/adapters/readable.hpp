#pragma once

#include <cstdint>
#include <stdexcept>
#include <type_traits>

namespace wirepump {

namespace traits {

template <typename, typename, typename> struct trait;

}

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

struct unexpected_eof : std::runtime_error {
    unexpected_eof()
        : std::runtime_error{"Unexpected end of stream"}
    {}
};

namespace adapters {

template <typename Stream>
class readable {
  public:
    static_assert(details::is_readable_v<std::decay_t<Stream>>, "Stream should look like an input stream");

    template<typename... Args>
    readable(Args&&... args)
      : m_stream{std::forward<Args>(args)...}
    {}

    template <typename T>
    T read() {
        return traits::trait<T, Stream, void>::read(*this);
    }
  
  protected:
    Stream m_stream;

    uint8_t read_byte() {
        auto ch = m_stream.get();
        if (m_stream.eof()) throw unexpected_eof{};
        return ch;
    }

    friend struct traits::trait<uint8_t, Stream, void>;
};

}

}
