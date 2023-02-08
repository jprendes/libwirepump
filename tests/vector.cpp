#include "./test_utils.hpp"
#include <vector>

using VariantType = std::variant<int, std::string>;
using ConfusingVariantType = std::variant<int, int>;

int main(void) {
    std::vector<int> some_int_vector{1, 2, 3, 4};
    std::vector<std::string> some_str_vector{"hello", "world"};

    assert_round_trip(std::vector<int>, some_int_vector);
    assert_size(std::vector<int>, some_int_vector, 5);

    assert_round_trip(std::vector<std::string>, some_str_vector);
    assert_size(std::vector<std::string>, some_str_vector, 1 + 6 + 6);

    return 0;
}
