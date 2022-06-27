inline void putChar(char c) {
    __asm__ (
        "mov %1, %%al;"
        "mov $0x0e, %%ah;"
        "int $0x20;"
        : "=r" ( *(int*)0 )
        : "r" ( c )
    );
}

extern "C" void PrintString(const char* str) {
    for (int i = 0; str[i] != 0; i++){
        if (str[i] == '\n')
            putChar('\r');
        putChar(str[i]);
    }
}
