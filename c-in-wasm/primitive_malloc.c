// primitive-malloc.c

// Use clang extensions to your heart's delight, it's
// your only C compiler.
#pragma clang assume_nonnull begin
typedef typeof(sizeof(1)) size_t;
enum {SIZE_T_SIZE=sizeof(size_t)};

// This will be defined by the instantiating wasm
// code.
extern unsigned char __heap_base[];

static unsigned char*_base_ptr = __heap_base;

// Useful function expose to javascript.
void
reset_memory(void){
    _base_ptr = __heap_base;
}

// The workhorse function.
// Just a bump allocator.
static inline
void*_Nonnull
alloc(size_t size, size_t alignment){
    if(alignment > SIZE_T_SIZE)
        alignment = SIZE_T_SIZE;
    size_t b = (size_t)_base_ptr;
    if(b & (alignment-1)){
        b += alignment - (b & (alignment-1));
        _base_ptr = (unsigned char*)b;
    }
    void* result = _base_ptr;
    _base_ptr += size;
    return result;
}

void*
malloc(size_t size){
    return alloc(size, 8);
}

void*
calloc(size_t n_items, size_t item_size){
    void* result = alloc(n_items*item_size, item_size);
    // Provided by bulk memory extension.
    __builtin_memset(result, 0, n_items*item_size);
    return result;
}

// Just don't do anything.
// You could improve this by maintaining a free list.
void
free(void*_Nullable p){
    (void)p;
}
#pragma clang assume_nonnull end
