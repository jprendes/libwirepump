#pragma once

#include <coroutine>
#include <utility>
#include <optional>

#include "wirepump/coroutines/result_holder.hpp"

namespace wirepump::coroutines {

template <typename T>
struct sync_task {
  public:
    struct promise_type;
    struct awaitable;

    sync_task() = delete;
    sync_task(sync_task const & other) = delete;
    sync_task(sync_task && other) = default;

    awaitable operator co_await() & = delete;
    awaitable operator co_await() const & = delete;
    awaitable operator co_await() && noexcept {
        auto handle = m_handle;
        m_handle = nullptr;
        return { handle };
    }

    T get() && noexcept {
        auto handle = m_handle;
        m_handle = nullptr;
        return awaitable{ handle }.await_resume();
    }

    operator T() && noexcept {
        return std::move(*this).get();
    }

    ~sync_task() {
        if (m_handle) m_handle.destroy();
    }

  private:
    std::coroutine_handle<promise_type> m_handle;
    sync_task(std::coroutine_handle<promise_type> handle) : m_handle(handle) {}
    friend promise_type;
};

template <typename T>
struct sync_task<T>::promise_type : public result_holder<T> {
  public:
    sync_task get_return_object() noexcept {
        return { std::coroutine_handle<promise_type>::from_promise(*this) };
    }
    constexpr std::suspend_never initial_suspend() noexcept { return {}; }
    constexpr std::suspend_always final_suspend() noexcept { return {}; }

  private:
    friend sync_task;
};

template <typename T>
struct sync_task<T>::awaitable {
  public:
    awaitable() = delete;
    awaitable(awaitable const & other) = delete;
    awaitable(awaitable && other) = default;

    constexpr bool await_ready() const noexcept { return true; }
    constexpr void await_suspend( std::coroutine_handle<> ) const noexcept { }
    T await_resume() {
        auto promise = std::move(m_handle.promise());
        m_handle.destroy();
        m_handle = nullptr;
        return std::move(promise).get();
    }

    ~awaitable() {
        if (m_handle) m_handle.destroy();
    }

  private:
    std::coroutine_handle<promise_type> m_handle;
    awaitable(std::coroutine_handle<promise_type> handle) : m_handle(handle) {}
    friend sync_task;
};

}
