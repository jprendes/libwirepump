#include <sstream>
#include <string>
#include <vector>

#include <wirepump.hpp>

struct Item {
    std::string name;
    float value;
    std::vector<std::string> tags;
    bool operator==(Item const &) const = default;
};

int main() {
    std::stringstream ss;

    // serialize
    Item pi_item{"pi", 3.14f, {"circle", "irrational"}};

    wirepump::write(ss, 42);
    wirepump::write(ss, pi_item);

    // deserialize
    int value;
    wirepump::read(ss, value);
    assert(value == 42);

    Item item;
    wirepump::read(ss, item);
    assert(item == pi_item);

    return 0;
}
