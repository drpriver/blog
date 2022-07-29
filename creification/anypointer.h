// anypointer.h
#include <stdio.h>

// prefixes and other types elided for brevity
enum AnyPointerTag {
    UNINIT,
    INT,
    CHAR_STAR,
    DOUBLE,
};
typedef struct AnyPointer AnyPointer;
struct AnyPointer {
    enum AnyPointerTag tag;
    union {
        void* pointer;
        int* integer;
        char** charstar;
        double* double_;
    };
};

void
print_any(AnyPointer any){
    switch(any.tag){
        case UNINIT: return;
        case INT:
            printf("%d\n", *any.integer);
            return;
        case CHAR_STAR:
            printf("%s\n", *any.charstar);
            return;
        case DOUBLE:
            printf("%f\n", *any.double_);
            return;
        default: return;
    }
}
