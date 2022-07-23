#define COMBINE(a, b) a##b
#define MAKE_MAX(T, prefix) \
  static inline \
  T COMBINE(prefix, max)(T a, T b){ \
      if(a > b) return a; \
      return b; \
  }
MAKE_MAX(int, int_)

#include <assert.h>
int main(void){
    int x = int_max(1, 2);
    assert(x == 2);
    return 0;
}
