#include "./test_utils.hpp"

int main(void) {
    assert_round_trip(uint16_t, 0x123);
    assert_size(uint16_t, 42, 1);

    assert_round_trip(int16_t, -0x123);
    assert_size(int16_t, 42, 1);
    assert_size(int16_t, -42, 1);

    assert_round_trip(uint32_t, 0x123456);
    assert_size(uint32_t, 42, 1);

    assert_round_trip(int32_t, -0x123456);
    assert_size(int32_t, 42, 1);
    assert_size(int32_t, -42, 1);

    assert_round_trip(uint64_t, 0x123456789);
    assert_size(uint64_t, 42, 1);

    assert_round_trip(int64_t, -0x123456789);
    assert_size(int64_t, 42, 1);
    assert_size(int64_t, -42, 1);

    return 0;
}
