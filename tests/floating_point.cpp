#include "./test_utils.hpp"

int main(void) {
    assert_round_trip(float, 3.14);
    assert_size(float, 3.14, 4);

    assert_round_trip(double, 3.14);
    assert_size(double, 3.14, 8);

    return 0;
}
