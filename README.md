# wirepump

A small header-only C++ library for serializing and deserializing data.

## Installation

```bash
git clone https://github.com/jprendes/libwirepump.git
cd libwirepump
cmake -B ./build/ -G Ninja
cmake --build ./build/
sudo cmake --install ./build/
```

## Getting started

To serialize/deserialize an object use the `wirepump::write`/`wirepump::read` methods.

It works out of the box with stream-like objects:
```c++
#include <sstream>
#include <string>
#include <vector>

#include <wirepump.hpp>

struct Item {
    std::string name;
    float value;
    std::vector<std::string> tags;
    bool operator==(Item const &) const = default;
};

int main() {
    std::stringstream ss;

    // serialize
    Item pi_item{"pi", 3.14f, {"circle", "irrational"}};

    wirepump::write(ss, 42);
    wirepump::write(ss, pi_item);

    // deserialize
    int value;
    wirepump::read(ss, value);
    assert(value == 42);

    Item item;
    wirepump::read(ss, item);
    assert(item == pi_item);

    return 0;
}
```

It also provides support for [asio](https://think-async.com/Asio/) objects.
```c++
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
```
