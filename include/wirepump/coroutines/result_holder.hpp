#include <optional>
#include <exception>

namespace wirepump::coroutines {

template <typename T>
struct result_holder;

template <>
struct result_holder<void> {
  private:
    std::exception_ptr m_exception = nullptr;

  public:
    constexpr result_holder() = default;
    constexpr result_holder(result_holder const &) = delete;
    result_holder(result_holder &&) = default;

    void unhandled_exception() noexcept {
        m_exception = std::current_exception();
    }

    constexpr void return_void() noexcept {}

    constexpr void get() && {
        if (m_exception) std::rethrow_exception(std::move(m_exception));
    }
};

template <typename T>
struct result_holder {
  private:
    std::optional<T> m_value = std::nullopt;
    std::exception_ptr m_exception = nullptr;

  public:
    constexpr result_holder() = default;
    constexpr result_holder(result_holder const &) = delete;
    result_holder(result_holder &&) = default;

    void unhandled_exception() noexcept {
        m_exception = std::current_exception();
    }

    void return_value(T && value)
        noexcept(requires (std::optional<T> opt, T val) {
            noexcept(opt = std::move(val));
        })
    {
        m_value = std::move(value);
    }

    constexpr T get() && {
        if (m_exception) std::rethrow_exception(std::move(m_exception));
        return std::move(m_value).value();
    }
};

}