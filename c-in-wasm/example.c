// example.c
#include "primitive_malloc.c"

extern void write(const char*, size_t);

void clicked(int i){
    char c[2] = {(i &0xf)+ 'a', '\n'};
    write(c, sizeof c);
}
