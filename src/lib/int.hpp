// C++ function wrappers for system interrupts

inline unsigned char inb(unsigned short port) {
    unsigned char ret;
    __asm__("in %%dx, %%al" : "=a"(ret) : "d"(port));
    return ret;
}

inline void outb(unsigned short port, unsigned char value) {
    __asm__("out %%al, %%dx" : : "a"(value), "d"(port));
}

inline unsigned short inw(unsigned short port) {
    unsigned short ret;
    __asm__("in %%dx, %%ax" : "=a"(ret) : "d"(port));
    return ret;
}

inline void outw(unsigned short port, unsigned short value) {
    __asm__("out %%ax, %%dx" : : "a"(value), "d"(port));
}

/*
 *  INT 0X20
 */

// ah 0x00
inline void putChar(char c) {
    __asm__ (
        "mov %1, %%al;"
        "mov $0x00, %%ah;"
        "int $0x20;"
        : "=r" ( *(int*)0 )
        : "r" ( c )
    );
}

// ah 0x01
inline void print(const char* str) {
    __asm__ (
        "mov %1, %%rdi;"
        "mov $0x01, %%ah;"
        "int $0x20;"
        : "=r" ( *(int*)0 )
        : "r" ( str )
    );
}

// ah 0x02
inline unsigned char getScancode() {
    unsigned char out;
    __asm__ (
        "mov $0x02, %%ah;"
        "int $0x20;"
        "mov %%al, %0"
        : "=r" ( out )
    );
    return out;
}

// ah 0x03
inline void setCursorPosition(unsigned short pos) {
    __asm__ (
        "mov %1, %%bx;"
        "mov $0x03, %%ah;"
        "int $0x20;"
        : "=r" ( *(int*)0 )
        : "r" ( pos )
    );
}

// ah 0x04
inline unsigned short getCursorPosition() {
    unsigned short pos;
    __asm__ (
        "mov $0x04, %%ah;"
        "int $0x20;"
        "mov %%bx, %0;"
        : "=r" ( pos )
    );
    return pos;
}

// ah 0x05
inline char* getScancodeSet() {
    char* ptr;
    __asm__ (
        "mov $0x05, %%ah;"
        "int $0x20;"
        "mov %%rdi, %0;"
        : "=r" ( ptr )
    );
    return ptr;
}

// ah 0x06
inline char* scan(char* str, long length) {
    char* out;
    __asm__ (
        "mov $0x06, %%ah;"
        "push %1;"
        "mov %2, %%rsi;"
        "int $0x20;"
        "mov %%rax, %0;"
        : "=r" ( out )
        : "r" ( str ),
        "r" ( length )
    );
    return out;
}