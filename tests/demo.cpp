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
    wirepump::write(ss, 42);
    wirepump::write(ss, Item{"pi", 3.14, {4, 3}});

    // deserialize
    int value;
    wirepump::read(ss, value);
    std::cout << value << "\n"; // 42

    Item item;
    wirepump::read(ss, item);
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
    wp_assert(capture.str() == expected, "Output should match the expected value");

    return 0;
}
