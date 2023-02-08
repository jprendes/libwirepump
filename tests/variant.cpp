#include "./test_utils.hpp"

using VariantType = std::variant<int, std::string>;
using ConfusingVariantType = std::variant<int, int>;

int main(void) {
    ConfusingVariantType confusing_variant{std::in_place_index<1>, 42};

    assert_round_trip(VariantType, "hello world");
    assert_size(VariantType, "hello world", 13);
    assert_size(VariantType, 42, 2);

    assert_round_trip(ConfusingVariantType, confusing_variant);

    return 0;
}
