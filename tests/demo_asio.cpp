#include <asio.hpp>
#include <string>
#include <vector>

#include <wirepump.hpp>

struct Item {
    std::string name;
    float value;
    std::vector<std::string> tags;
    bool operator==(Item const &) const = default;
};

asio::awaitable<void> async_main(asio::io_context & ctx) {
    asio::local::stream_protocol::socket source{ctx};
    asio::local::stream_protocol::socket sink{ctx};
    asio::local::connect_pair(source, sink);

    Item pi_item{"pi", 3.14f, {"circle", "irrational"}};

    co_await wirepump::write(sink, 42);
    co_await wirepump::write(sink, pi_item);

    int value;
    co_await wirepump::read(source, value);
    assert(value == 42); // ✓ ok

    Item item;
    co_await wirepump::read(source, item);
    assert(item == pi_item); // ✓ ok
}

int main(void) {
    asio::io_context ctx(1);
    auto result = asio::co_spawn(ctx, async_main(ctx), asio::use_future);
    ctx.run();
    result.get();
    return 0;
}