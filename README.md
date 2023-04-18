# wirepump

A small header-only C++ library for serializing and deserializing data.

## Installation

```bash
git clone https://github.com/jprendes/libwirepump.git
cd libwirepump
cmake -B ./build/ -G Ninja
cmake --build ./build/
sudo cmake --install ./build/
```

## Getting started

To serialize/deserialize an object wrap it with a `wirepump::serialized` and pipe it to/from a stream.
```c++
#include <wirepump.hpp>

struct Item {
    std::string name;
    float value;
    struct {
        int x, y;
    } position;
};

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
```
