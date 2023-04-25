#include "./test_utils.hpp"
#include <optional>

int main(void) {
    assert_round_trip(std::optional<int>, std::nullopt);
    assert_size(std::optional<int>, std::nullopt, 1);

    assert_round_trip(std::optional<int>, 42);
    assert_size(std::optional<int>, 42, 2);

    return 0;
}
