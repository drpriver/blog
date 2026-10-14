// map.c
#define CAT(a, b) CAT_(a, b)
#define CAT_(a, b) a##b
#define NARG(...) NARG_(__VA_ARGS__ __VA_OPT__(,) 8,7,6,5,4,3,2,1,0)
#define NARG_(_1,_2,_3,_4,_5,_6,_7,_8,N,...) N
#define MAP_0(m)
#define MAP_1(m, x)      m(x)
#define MAP_2(m, x, ...) m(x) MAP_1(m, __VA_ARGS__)
#define MAP_3(m, x, ...) m(x) MAP_2(m, __VA_ARGS__)
#define MAP_4(m, x, ...) m(x) MAP_3(m, __VA_ARGS__)
#define MAP_5(m, x, ...) m(x) MAP_4(m, __VA_ARGS__)
#define MAP_6(m, x, ...) m(x) MAP_5(m, __VA_ARGS__)
#define MAP_7(m, x, ...) m(x) MAP_6(m, __VA_ARGS__)
#define MAP_8(m, x, ...) m(x) MAP_7(m, __VA_ARGS__)
#define __map(m, ...) CAT(MAP_, NARG(__VA_ARGS__))(m __VA_OPT__(,) __VA_ARGS__)
int x = 1;
int y = 2;
int z = 3;

#define PRINTINT(x) printf(#x " = %d\n", x);
int printf(const char*, ...);
int main(){
    __map(PRINTINT, 1, 2, 3, 4, x, y, z)
}
