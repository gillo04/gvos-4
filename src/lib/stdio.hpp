/*
 * Mapping interrupts to functions
 */

inline void putChar(char c) {
    __asm__ (
        "mov %1, %%al;"
        "mov $0x00, %%ah;"
        "int $0x20;"
        : "=r" ( *(int*)0 )
        : "r" ( c )
    );
}

inline void print(const char* str) {
    __asm__ (
        "mov %1, %%rdi;"
        "mov $0x01, %%ah;"
        "int $0x20;"
        : "=r" ( *(int*)0 )
        : "r" ( str )
    );
}

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

inline void setCursorPosition(unsigned short pos) {
    __asm__ (
        "mov %1, %%bx;"
        "mov $0x03, %%ah;"
        "int $0x20;"
        : "=r" ( *(int*)0 )
        : "r" ( pos )
    );
}

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

/*
 * String utilities
 */

// Unsigned int to string
// Handles from binary to hexadecimal
const char* utos(unsigned long num, unsigned int base, char* str) {
    if (base < 2 || base > 16) {
        return str;
    }

    int i = 0;
    do {
        str[i] = (num % base < 10) ? num % base + '0' : num % base + 'A' - 10;
        num /= base;
        i++;
    } while (num != 0);
    str[i] = 0;

    for (int j = 0; j < i/2; j++) {
        char tmp = str[j];
        str[j] = str[i-1-j];
        str[i-1-j] = tmp;
    }
    

    return str;
}

// Int to string
// Handles from binary to hexadecimal
const char* itos(long num, unsigned int base, char* str) {
    if (num < 0){
        num = -num;
        str[0] = '-';
        return utos(num, base, str+1)-1;
    }

    return utos(num, base, str);
}

unsigned int stou(const char* str) {
    unsigned int num = 0;
    int i = 0;
    while (str[i] != 0) {
        i ++;
    }

    int pow = 1;
    for (i--; i >= 0; i--){
        num += (str[i] - '0') * pow;
        pow *= 10;
    }

    return num;
}