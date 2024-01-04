#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// Define these as makes sense.
uint32_t hash_key(const KeyType* key);
_Bool key_eq(const KeyType* a, const KeyType* b);

// You'll probably name these something else in your
// implementation to avoid collisions.
typedef struct Pair Pair;
struct Pair {
  KeyType key;
  ValueType value;
};

typedef struct Table Table;
struct Table {
  uint32_t count, capacity;
  Pair* data;
};

enum {TABLE_EMPTY_SLOT=UINT32_MAX};

// Grows the table to the new size.
// Returns 0 on success and non-zero on failure (usually
// allocation failure).
int
grow_table(Table* table, size_t new_size);

// If key is already in the table, returns the pointer to
// the corresponding value.
// Otherwise, inserts the key into the table and returns a
// pointer to the uninitialized value.
// Returns NULL if the table needed to grow and that
// failed.
ValueType*
table_getsert(Table* table, KeyType* key);

// If key is in the table, returns the pointer to the
// corresponding value.
// Otherwise returns NULL.
ValueType*
table_has(const Table* table, const KeyType* key);

// This is faster than modulo while preserving the same
// properties if all the bits are equally well distributed.
// Do *not* use identity hash with this.
uint32_t
fast_reduce32(uint32_t x, uint32_t y){
  return ((uint64_t)x * (uint64_t)y) >> 32;
}

int
grow_table(Table* table, size_t new_cap){
  size_t cap = table->capacity;
  if(new_cap <= cap) return 0;
  if(new_cap > UINT32_MAX/2) return 1;

  // On a 32 bit system, you'll want to check
  // for overflow here.
  size_t new_size = new_cap*(sizeof(Pair)
                    +2*sizeof(uint32_t));
  char* new_data = realloc(table->data, new_size);
  if(!new_data) return 1;
  table->data = (Pair*)new_data;
  table->capacity = (uint32_t)new_cap;

  size_t offset = new_cap * sizeof(Pair);
  uint32_t* indexes = (uint32_t*)(new_data+offset);
  size_t idx_cap = 2*new_cap;
  memset(indexes, 0xff, idx_cap * sizeof *indexes);

  Pair* items = (Pair*)new_data;
  for(size_t i = 0; i < table->count; i++){
    Pair* p = &items[i];
    uint32_t hash = hash_key(&p->key);
    uint32_t idx = fast_reduce32(hash, (uint32_t)idx_cap);
    while(indexes[idx] != TABLE_EMPTY_SLOT){
      idx++;
      if(idx == idx_cap) idx = 0;
    }
    indexes[idx] = i;
  }
  return 0;
}

ValueType*
table_getsert(Table* table, KeyType* key){
  if(table->count == table->capacity){
    size_t new_cap;
    if(table->capacity)
        new_cap = 2*table->capacity;
    else
        new_cap = 32;
    int err = grow_table(table, new_cap);
    if(err) return NULL;
  }
  uint32_t cap = table->capacity;
  uint32_t idx_cap = cap * 2;
  uint32_t hash = hash_key(key);
  uint32_t idx = fast_reduce32(hash, idx_cap);

  size_t offset = cap * sizeof(Pair);
  char* data = (char*)table->data;
  uint32_t* indexes = (uint32_t*)(data + offset);
  Pair* items = table->data;
  for(;;){
    uint32_t i = indexes[idx];
    if(i == TABLE_EMPTY_SLOT){
      indexes[idx] = table->count;
      items[table->count].key = *key;
      return &items[table->count++].value;
    }

    Pair* p = &items[i];
    if(key_eq(&p->key, key))
      return &p->value;

    idx++;
    if(idx == idx_cap) idx = 0;
  }
}

ValueType*
table_has(const Table* table, const KeyType* key){
  if(!table->count) return NULL; // empty table
  uint32_t cap = table->capacity;
  uint32_t idx_cap = cap * 2;
  uint32_t hash = hash_key(key);
  uint32_t idx = fast_reduce32(hash, idx_cap);

  size_t offset = cap * sizeof(Pair);
  char* data = (char*)table->data;
  uint32_t* indexes = (uint32_t*)(data + offset);
  Pair* items = table->data;
  for(;;){
    uint32_t i = indexes[idx];
    if(i == TABLE_EMPTY_SLOT)
      return NULL;

    Pair* p = &items[i];
    if(key_eq(&p->key, key))
      return &p->value;

    idx++;
    if(idx == idx_cap) idx = 0;
  }
}
