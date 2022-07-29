// generic_tag.c
#include "anypointer.h"

#define TAG(x) _Generic(x, \
    int: INT, \
    char*: CHAR_STAR, \
    double: DOUBLE)

int main(void){
    int x = 3;
    AnyPointer any = {.tag=TAG(x), .pointer=&x};
    print_any(any); // prints 3
    return 0;
}
