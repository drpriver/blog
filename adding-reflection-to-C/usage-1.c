#include "option-1.c"

int main(void){
    struct Foo f = {
        1, 2,
        .is_baz = 1,
        .is_bar = 0,
        .is_foo = 1,
    };
    print_as_json(&typeinfo_Foo.info, &f);
    // {"x": 1, "y": 2, "is_baz": 1, "is_bar": 0, "is_foo": 0}
    // oops: `is_foo` is wrong
    return 0;
}
