#include <stdio.h>

//typedef void (*Say_Hello_Function) (char *);
//extern __declspec(dllimport) Say_Hello_Function say_hello;

extern void __declspec(dllimport) libhello_init(void);
extern void __declspec(dllimport) say_hello(char *);

int main(void) {
    libhello_init();

    fprintf(stderr, "say_hello: %p\n", &say_hello);
    say_hello("Ethan");
    return 0;
}

