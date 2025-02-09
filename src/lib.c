#include <stdio.h>

typedef void (*Say_Hello_Function) (char *);
__declspec(dllexport) Say_Hello_Function say_hello = NULL;

extern void __declspec(dllexport) say_hello_impl(char *name) {
    fprintf(stderr, "Hello, %s!", name);
}

extern void __declspec(dllexport) libhello_init(void) {
    say_hello = &say_hello_impl;
}

