# wirepump

A small header-only C++ library for serializing and deserializing data.

## Installation

```bash
git clone https://github.com/jprendes/libwirepump.git
cd libwirepump
git submodule update --init --recursive
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
ss << wirepump::serialized(42);
ss << wirepump::serialized(Item{"pi", 3.14, {4, 3}});

// deserialize
int value;
ss >> wirepump::serialized(value);
std::cout << value << "\n"; // 42

Item item;
ss >> wirepump::serialized(item);
std::cout << item.name << "=" << item.value << "\n"; // pi=3.14
```
