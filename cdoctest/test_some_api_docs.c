// test_some_api_docs.c
#include <assert.h>
#define SOME_API_EXAMPLE
#include "some_api.h"

int main(void){
    int data[3] = {1, 2, 3};
    SomeApiContext* ctx = some_api_create();
    some_api_store_data(ctx, data, 3);
    assert(sum_some_api_data(ctx) == 6);
    return 0;
}
