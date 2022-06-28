#define SCREEN_COLS 80
#define SCREEN_ROWS 25

inline void putChar(char c) {
    __asm__ (
        "mov %1, %%al;"
        "mov $0x00, %%ah;"
        "int $0x20;"
        : "=r" ( *(int*)0 )
        : "r" ( c )
    );
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

extern "C" void PrintString(const char* str) {
    for (int i = 0; str[i] != 0; i++){
        if (str[i] == '\n')
            setCursorPosition((getCursorPosition() / SCREEN_COLS + 1) * SCREEN_COLS);
        else
            putChar(str[i]);
    }
}

extern "C" char* ScanString(char* str, long length) {
    char* ScanCodeSet1;
    __asm__ (
        "mov $0x05, %%ah;"
        "int $0x20;"
        "mov %%rdi, %0;"
        : "=r" ( ScanCodeSet1 )
    );
    unsigned char scanCode;
    
    int i = 0;
    while (true){
        // Acquire key press
        __asm__ (
            "mov $0x02, %%ah;"
            "int $0x20;"
            "mov %%al, %0"
            : "=r" ( scanCode )
        );

        // Break
        if (scanCode == 0x1C)
            break;

        if (ScanCodeSet1[scanCode] == 0 || scanCode > 0x80)
            continue;

        // Delete
        if (scanCode == 0x0e) {
            if (i <= 0)
                continue;

            unsigned short pos = getCursorPosition() - 1;
            setCursorPosition(pos);
            putChar(' ');
            setCursorPosition(pos);
            i --;
            continue;
        }

        // Print
        if (i < length) {
            str[i] = ScanCodeSet1[scanCode];
            putChar(ScanCodeSet1[scanCode]);
            i ++;
        }

    }
    str[i] = 0;
    return str;
}