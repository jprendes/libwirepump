#include "test_utils.hpp"

#include <wirepump.hpp>

struct Item {
    std::string name;
    float value;
    struct {
        int x, y;
    } position;
};

void demo() {
    std::stringstream ss;

    // serialize
    ss << wirepump::serialized(42);
    ss << wirepump::serialized(Item{"pi", 3.14, {4, 3}});

    // deserialize
    int value;
    ss >> wirepump::serialized(value);
    std::cout << value << "\n"; // 42

    Item item;
    ss >> wirepump::serialized(item);
    std::cout << item.name << "=" << item.value << "\n"; // pi=3.14
}

int main(void) {
    std::stringstream capture;
    auto cout_buff = std::cout.rdbuf();
    std::cout.rdbuf(capture.rdbuf());

    demo();

    std::cout.rdbuf(cout_buff);
 
    auto expected = 
        "42\n"
        "pi=3.14\n";
    assert(capture.str() == expected, "Output should match the expected value");

    return 0;
}
