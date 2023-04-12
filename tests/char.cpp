#include "./test_utils.hpp"

int main(void) {
    assert_round_trip(uint8_t, 42);
    assert_size(uint8_t, 42, 1);
    assert_size(uint8_t, 0xff, 1);

    assert_round_trip(char, 42);
    assert_size(char, 42, 1);
    assert_size(uint8_t, -1, 1);

    return 0;
}
