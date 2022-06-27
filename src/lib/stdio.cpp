#include "stdio.h"

void putChar(char c) {
    __asm__ (
        "mov %1, %%al;"
        "mov $0x0e, %%ah;"
        "int $0x20;"
        : "=r" ( *(int*)0 )
        : "r" ( c )
    );
}

void print(const char* str) {
    __asm__ (
        "mov %1, %%rdi;"
        "mov $0x01, %%ah;"
        "int $0x20;"
        : "=r" ( *(int*)0 )
        : "r" ( str )
    );
}