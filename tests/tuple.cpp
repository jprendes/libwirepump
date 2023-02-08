#include "./test_utils.hpp"

using TupleType = std::tuple<std::string, double, std::tuple<int, int>>;

using ArrayType = std::array<int, 3>;

struct StructType {
    std::string name;
    double value;

    struct {
        int x;
        int y;
    } position;

    bool operator==(StructType const & other) const {
        return name == other.name
            && value == other.value
            && position.x == other.position.x
            && position.y == other.position.y;
    }
};

int main(void) {
    TupleType some_tuple{"pi", 3.14, { 3, 4 }};
    StructType some_struct{"pi", 3.14, { 3, 4 }};
    ArrayType some_array{1, 2, 3};

    assert_round_trip(TupleType, some_tuple);
    assert_size(TupleType, some_tuple, 3 + 8 + 2);

    assert_round_trip(StructType, some_struct);
    assert_size(StructType, some_struct, 3 + 8 + 2);

    assert_round_trip(ArrayType, some_array);
    assert_size(ArrayType, some_array, 3);

    return 0;
}
