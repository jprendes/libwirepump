#include "./test_utils.hpp"

int main(void) {
    assert_round_trip(std::string, "hello world");
    assert_size(std::string, "hello world", 12);

    return 0;
}
