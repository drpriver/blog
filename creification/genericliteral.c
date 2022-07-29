// generic_compound.c
#include "anypointer.h"

// NOTE: we now take a pointer instead of the value
#define TAG(x) _Generic(x, \
    int*: INT, \
    char**: CHAR_STAR, \
    double*: DOUBLE)

#define ANY(x) (AnyPointer){.tag=TAG(x), .pointer=x}

int main(void){
    int x = 3;
    AnyPointer any = ANY(&x);
    print_any(any); // prints 3
    return 0;
}
