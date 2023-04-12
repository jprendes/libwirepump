#pragma once

#include <coroutine>

namespace wirepump::adapters::coroutines {

struct sync_void_awaitable {
    struct promise_type {
        constexpr sync_void_awaitable get_return_object() noexcept {
            return {};
        }
        constexpr std::suspend_never initial_suspend() const noexcept {
            return {};
        }
        constexpr std::suspend_never final_suspend() const noexcept {
            return {};
        }

        void unhandled_exception() {
            throw;
        }
        constexpr void return_void() noexcept {}
    };

    constexpr bool await_ready() const noexcept {
        return true;
    }
    constexpr bool await_suspend(std::coroutine_handle<>) const noexcept {
        return false;
    }
    constexpr void await_resume() const {}
};

}
