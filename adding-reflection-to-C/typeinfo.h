// typeinfo.h
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
struct TypeInfo {
    const char *name;
    size_t size, align;
    size_t fields;
    struct FieldInfo {
        const struct TypeInfo *type;
        const char* name;
        size_t offset;
        _Bool is_bitfield;
        size_t bf_width;
        size_t bf_offset;
    } field[1]; // fake FAM, so it can be a member of a union
};
#define TYPEINFO_INT32 (struct TypeInfo*)0x1
#define TYPEINFO_UINT32 (struct TypeInfo*)0x2
void print_as_json(const struct TypeInfo* ti, const void* data){
    if(ti == TYPEINFO_INT32){
        printf("%d", *(const int*)data);
        return;
    }
    if(ti == TYPEINFO_UINT32){
        printf("%u", *(const unsigned*)data);
        return;
    }
    printf("{");
    for(size_t i = 0; i < ti->fields; i++){
        if(i != 0) printf(", ");
        const struct FieldInfo* fi = &ti->field[i];
        printf("\"%s\": ", fi->name);
        const void* base = (const char*)data + fi->offset;
        if(fi->is_bitfield){
            uint32_t v = *(uint32_t*)base;
            v >>= fi->bf_offset;
            uint32_t mask = (1u << fi->bf_width) - 1;
            v &= mask;
            printf("%u", v);
        }
        else
            print_as_json(fi->type, base);
    }
    printf("}");
}
