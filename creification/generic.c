// generic.c
#include <stdio.h>

int main(void){
    // prints: "int: 3"
    printf(
        _Generic(3,
        int: "int: %d\n",
        float: "float: %f\n"), 3);
    return 0;
}
