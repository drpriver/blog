// example.c
#include "anypointer.h"

int main(void){
    int x = 3;
    AnyPointer any = {.tag=INT, .integer=&x};
    print_any(any); // prints 3
    return 0;
}
