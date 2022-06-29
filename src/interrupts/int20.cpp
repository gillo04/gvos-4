#define SCREEN_COLS 80
#define SCREEN_ROWS 25

#include "../lib/int.hpp"

extern "C" void PrintString(const char* str) {
    for (int i = 0; str[i] != 0; i++){
        if (str[i] == '\n')
            setCursorPosition((getCursorPosition() / SCREEN_COLS + 1) * SCREEN_COLS);
        else
            putChar(str[i]);
    }
}

extern bool CapsLock;
extern bool Shift;
extern "C" char* ScanString(char* str, long length) {
    // Fetch the keyboard layout
    char* ScanCodeSet1 = getScancodeSet();
    unsigned char scanCode;
    
    int i = 0;
    while (true){
        scanCode = getScancode();
        
        // Enter
        if (scanCode == 0x1C)
            break;

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

        // Caps lock
        if (scanCode == 0x3a) {
            CapsLock = !CapsLock;
            continue;
        }

        // Shift press
        if (scanCode == 0x2a || scanCode == 0x36) {
            Shift = true;
            continue;
        }

        // Shift release
        if (scanCode == 0x2a + 0x80 || scanCode == 0x36 + 0x80) {
            Shift = false;
            continue;
        }

        // Print
        if (i < length && ScanCodeSet1[scanCode] != 0 && scanCode <= 0x80) {
            char final = ScanCodeSet1[scanCode];
            char letterTail;
            if (final >= 'A' && final <= 'Z'){
                letterTail = (CapsLock != Shift) ? 0b01000000 : 0b01100000;
                final = letterTail | (final & 0x1f);
            }
            str[i] = final;
            putChar(final);
            i ++;
        }

    }
    str[i] = 0;
    return str;
}