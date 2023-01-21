// js-strings.c

// I've found wrapping APIs this way is easiest
// for me.
typedef struct PrefixedString PrefixedString;
struct PrefixedString {
    size_t length;
    unsigned char data[];
};

static
void some_api(size_t length, const char* txt);

void
some_api_js(PrefixedString* ps){
    some_api(ps->length, (char*)ps->data);
}
