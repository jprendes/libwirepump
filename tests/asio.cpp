#include "./test_utils.hpp"
#include "asio/this_coro.hpp"
#include "asio/use_awaitable.hpp"
#include "asio/use_future.hpp"

#include <asio.hpp>
#include <asio/io_service.hpp>
#include <asio/local/stream_protocol.hpp>
#include <asio/local/connect_pair.hpp>
#include <asio/co_spawn.hpp>
#include <asio/detached.hpp>
#include <asio/awaitable.hpp>
#include <asio/experimental/awaitable_operators.hpp>

#include <wirepump.hpp>

#include <string>

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

    // Use an intermediate variable since gcc doesn't like the commented out version.
    // co_await wirepump::write(socket, my_struct{ 42, "hitchhiker" });
    auto struct_msg = my_struct{ 42, "hitchhiker" };
    co_await wirepump::write(socket, struct_msg);
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
