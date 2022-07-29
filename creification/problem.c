// problem.c
#include "anypointer.h"

int main(void){
    int x = 3;
    AnyPointer any = {.tag=CHAR_STAR, .integer=&x};
    print_any(any); // segfaults
}
