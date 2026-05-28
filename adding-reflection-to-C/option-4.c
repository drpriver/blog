#include <stdint.h>

struct Foo { 
    int32_t x, y; 
    uint32_t is_baz: 1,
             is_bar: 1,
             is_foo: 1,
             _padding: 29;
};
