// some_api.h
#include <stddef.h> // size_t
typedef struct SomeApiContext SomeApiContext;

// Visibility modifiers, dllexport, and some documentation
// elided for brevity.

SomeApiContext* some_api_create(void);
// ...

void some_api_store_data(SomeApiContext*, int*, size_t);
// ...

size_t
some_api_get_data(
    SomeApiContext* ctx, 
    int* buff, size_t bufflen, 
    size_t* cookie);
// Copies the data into a user provided buffer.
//
// Arguments:
// ----------
// ctx:
//      The api context
// buff:
//      The buffer to copy the data into.
// bufflen:
//      The length (in items, not bytes) of buff.
// cookie:
//      A pointer to an opaque value for remembering where
//      in the data this function is. Initialize cookie to 0
//      before calling this function.
// 
// Returns:
// --------
// The number of items copied into buff. If 0 is returned,
// no items were copied into the buff and there are no more
// items to copy.
//
// Example:
// --------
#ifdef SOME_API_EXAMPLE
int sum_some_api_data(SomeApiContext* ctx){
    int result = 0;
    enum {buff_len=32};
    int buff[buff_len];
    size_t n = 0;
    size_t cookie = 0;
    while((n = some_api_get_data(ctx, buff, buff_len, &cookie))){
        for(size_t i = 0; i < n; i++){
            result += buff[i];
        }
    }
    return result;
}
#endif // SOME_API_EXAMPLE
