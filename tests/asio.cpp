#include "./test_utils.hpp"

#include <asio.hpp>
#include <asio/experimental/awaitable_operators.hpp>

#include <wirepump.hpp>

#include <string>

#if defined(__GNUC__) && !defined(__clang__)
#  include <features.h>
#  if !__GNUC_PREREQ(13,0)
#    define _WIREPUMP_OLDER_GCC
#  endif
#endif

using namespace std::literals;
using namespace asio::experimental::awaitable_operators;

struct my_struct {
    int life;
    std::string name;
};

asio::awaitable<void> server(asio::local::stream_protocol::socket socket) {
    std::string text_msg;
    co_await wirepump::read(socket, text_msg);
    wp_assert(text_msg == "hello world!", "Unexpected message");

    co_await wirepump::write(socket, 3.1415926);

    my_struct struct_msg;
    co_await wirepump::read(socket, struct_msg);
    wp_assert(struct_msg.life == 42, "Unexpected message");
    wp_assert(struct_msg.name == "hitchhiker", "Unexpected message");
}

asio::awaitable<void> client(asio::local::stream_protocol::socket socket) {
    co_await wirepump::write(socket, "hello world!"sv);

    double double_msg;
    co_await wirepump::read(socket, double_msg);
    wp_assert(double_msg == 3.1415926, "Unexpected message");

#if defined(_WIREPUMP_OLDER_GCC)
    // Use an intermediate variable for `my_struct` in older gcc versions.
    // Looks like a compiler bug fixed in gcc 13.
    // See https://godbolt.org/z/q1nMdej1W
    auto struct_msg = my_struct{ 42, "hitchhiker" };
    co_await wirepump::write(socket, struct_msg);
#else
    co_await wirepump::write(socket, my_struct{ 42, "hitchhiker" });
#endif
}

asio::awaitable<int> async_main(asio::io_context & io_context) {
    asio::local::stream_protocol::socket server_socket{io_context};
    asio::local::stream_protocol::socket client_socket{io_context};

    asio::local::connect_pair(client_socket, server_socket);
    
    co_await (server(std::move(server_socket)) && client(std::move(client_socket)));

    co_return 0;
}

int main(void) {
    asio::io_context io_context(1);

    auto result = asio::co_spawn(io_context, async_main(io_context), asio::use_future);

    io_context.run();

    return result.get();
}
