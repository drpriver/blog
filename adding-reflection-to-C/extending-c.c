#include <stdint.h>
#include <stddef.h>
struct Foo { 
    int32_t x, y; 
    uint32_t is_baz: 1,
             is_bar: 1,
             is_foo: 1,
             _padding: 29;
};
_Type T = struct Foo; // types as values
void print_as_json(_Type T, const void* data){
    if(T == int){
        printf("%d", *(const int*)data);
        return;
    }
    if(T == unsigned){
        printf("%u", *(const unsigned*)data);
        return;
    }
    printf("{");
    for(size_t i = 0; i < T.fields; i++){
        auto fi = T.field(i);
        if(fi.name[0] == '_') continue;
        if(i != 0) printf(", ");
        printf("\"%s\": ", fi.name);
        const void* base = (const char*)data + fi.offset;
        if(fi.is_bitfield){
            uint32_t v = *(uint32_t*)base;
            v >>= fi.bitoffset;
            uint32_t mask = (1u << fi.bitwidth) - 1;
            v &= mask;
            printf("%u", v);
        }
        else
            print_as_json(fi.type, base);
    }
    printf("}");
}
print_as_json(T, &(struct Foo){1, 2, .is_baz=1, .is_bar=0, .is_foo=1});
// {"x": 1, "y": 2, "is_baz": 1, "is_bar": 0, "is_foo": 1}
