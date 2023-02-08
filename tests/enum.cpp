#include "./test_utils.hpp"

enum class EnumClass { ONE, TWO, THREE };
enum class EnumClassI32: int32_t { ONE, TWO, THREE };
enum class EnumClassU64 : uint64_t { ONE, TWO, THREE };
enum Enum { ONE, TWO, THREE };

int main(void) {
    assert_round_trip(EnumClass, EnumClass::TWO);
    assert_size(EnumClass, EnumClass::TWO, 1);

    assert_round_trip(EnumClassI32, EnumClassI32::TWO);
    assert_size(EnumClassI32, EnumClassI32::TWO, 1);

    assert_round_trip(EnumClassU64, EnumClassU64::TWO);
    assert_size(EnumClassU64, EnumClassU64::TWO, 1);

    assert_round_trip(Enum, Enum::TWO);
    assert_size(Enum, Enum::TWO, 1);

    return 0;
}
