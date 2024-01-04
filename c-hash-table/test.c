typedef int KeyType;
typedef int ValueType;
#include "ctable.c"
#include <assert.h>
#include <stdio.h>

uint32_t hash_key(const KeyType* key){
    uint32_t x = *key;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = (x >> 16) ^ x;
    return x;
}

_Bool key_eq(const KeyType* a, const KeyType* b){
    return *a == *b;
}

int main(int arg, char** argv){
    Table t = {0};
    for(int i = 0; i < 1024*1024; i++){
        *table_getsert(&t, &i) = i;
        if(0)
        for(int j = 0; j <= i; j++){
            assert(t.data[j].key == j);
            assert(t.data[j].value == j);
            assert(table_has(&t, &j));
            assert(*table_has(&t, &j) == j);
        }
    }
    for(int i = 0; i < 1024*1024; i++){
        assert(t.data[i].key == i);
        assert(t.data[i].value == i);
        assert(table_has(&t, &i));
        assert(*table_has(&t, &i) == i);
    }
    return 0;
}
