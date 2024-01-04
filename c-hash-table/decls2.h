#include <stdlib.h>
typedef int KeyType;
typedef int ValueType;
typedef struct Pair Pair;

struct Pair {
    KeyType key;
    ValueType value;
};
struct {
    size_t count, capacity;
    Pair* data;
} table;
