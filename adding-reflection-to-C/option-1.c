// option-1.c
#include "typeinfo.h"
struct Foo { 
    int32_t x, y; 
    union {
        uint32_t bf_bits; // fake field as you can't 
                          // take the address of a bitfield
        uint32_t is_baz: 1,
                 is_bar: 1,
                 is_foo: 1,
                 _padding: 29;
    };
};
const struct FooInfo {
    union {
        struct TypeInfo info;
        struct {
            const char *name;
            size_t size, align;
            size_t fields;
            struct FieldInfo field[5];
        };
    };
} typeinfo_Foo = {
    .name = "Foo",
    .size = sizeof(struct Foo),
    .align = _Alignof(struct Foo),
    .fields = 5,
    .field = {
        {
            .type = TYPEINFO_INT32,
            .name = "x",
            .offset = offsetof(struct Foo, x),
        },
        {
            .type = TYPEINFO_INT32,
            .name = "y",
            .offset = offsetof(struct Foo, y),
        },
        {
            .type = TYPEINFO_UINT32,
            .name = "is_baz",
            .offset = offsetof(struct Foo, bf_bits),
            .is_bitfield = 1, // no intrinsic to detect this
            .bf_width = 1, // no intrinsic to get this
            .bf_offset = 0, // no intrinsic to get this
        },
        {
            .type = TYPEINFO_UINT32,
            .name = "is_bar",
            .offset = offsetof(struct Foo, bf_bits),
            .is_bitfield = 1, // no intrinsic to detect this
            .bf_width = 1, // no intrinsic to get this
            .bf_offset = 1, // no intrinsic to get this
        },
        {
            .type = TYPEINFO_UINT32,
            .name = "is_foo",
            .offset = offsetof(struct Foo, bf_bits),
            .is_bitfield = 1, // no intrinsic to detect this
            .bf_width = 1, // no intrinsic to get this
            .bf_offset = 1, // no intrinsic to get this
        },
    },
};
