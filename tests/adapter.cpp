#include "test_utils.hpp"

struct reader {
    std::stringstream & ss;
};

struct writer {
    std::stringstream & ss;
};

namespace wirepump {

template <>
struct wirepump::read_impl<reader, uint8_t> {
    static auto read(reader & c, uint8_t & ch) -> coroutines::sync_task<void> {
        ch = c.ss.get();
        if (c.ss.eof()) throw unexpected_eof{};
        co_return;
    }
};

template <>
struct wirepump::write_impl<writer, uint8_t> {
    static auto write(writer & c, uint8_t const & ch) -> coroutines::sync_task<void> {
        c.ss.put(ch);
        co_return;
    }
};

}

int main(void) {
    std::stringstream ss;

    reader r{ss};
    writer w{ss};

    wirepump::write(w, 123);

    int value;
    wirepump::read(r, value);

    wp_assert(value == 123, "Value should be unchanged after a round-trip");
}
