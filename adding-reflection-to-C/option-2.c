// option-2.c
#include "typeinfo.h"
// X(parentname, pre, TI_TYPE, type, name, suffix, bf_offset, bf_width, addrmember, end)
#define XFOO(X) \
  X(Foo, , TYPEINFO_INT32, int32_t, x, , 0, 0, x, ) \
  X(Foo, , TYPEINFO_INT32, int32_t, y, , 0, 0, y, ) \
  X(Foo, union { uint32_t bf_bits; struct {, TYPEINFO_UINT32, uint32_t, is_baz, :1, 0, 1, bf_bits,) \
  X(Foo, , TYPEINFO_UINT32, uint32_t, is_bar, :1, 1, 1, bf_bits, ) \
  X(Foo, , TYPEINFO_UINT32, uint32_t, is_foo, :1, 2, 1, bf_bits, uint32_t _padding: 29;};};) \

struct Foo { 
#define X(parentname, pre, TI_TYPE, type, name, suffix, bf_offset, bf_width, addrmember, end) \
    pre type name suffix; end
    XFOO(X)
#undef X
};
typedef struct Foo Foo;
enum {
#define X(parentname, pre, TI_TYPE, type, name, suffix, bf_offset, bf_width, addrmember, end) \
    FOO__##name,
    XFOO(X)
#undef X
    FOO__count,
};
#define TYPEINFO(X, XMACRO, typename, CAPSNAME) \
    const struct typename##Info { \
        union { \
        struct TypeInfo info; \
        struct { \
            const char *name; \
            size_t size, align; \
            size_t fields; \
            struct FieldInfo field[CAPSNAME##__count]; \
        }; \
    }; \
} typeinfo_##typename = { \
  .name = #typename, \
  .size = sizeof(typename), \
  .align = _Alignof(typename), \
  .fields = CAPSNAME##__count, \
  .field = { \
      XMACRO(X) \
  } \
}
#define XFIELDINFO(parentname, pre, TI_TYPE, type_, fieldname, suffix, bf_offset_, bf_width_, addrmember, end) \
    { \
        .name = #fieldname, \
        .type = TI_TYPE, \
        .offset = offsetof(parentname, addrmember), \
        .is_bitfield = !!bf_width_, \
        .bf_offset = bf_offset_, \
        .bf_width = bf_width_, \
    },
TYPEINFO(XFIELDINFO, XFOO, Foo, FOO);
