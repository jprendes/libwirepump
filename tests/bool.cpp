#include "./test_utils.hpp"

int main(void) {
    assert_round_trip(bool, true);
    assert_size(bool, true, 1);
    assert_size(bool, false, 1);

    return 0;
}
