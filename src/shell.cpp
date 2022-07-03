#include "./lib/stdio.hpp"

void DrawTopBar(){
    setColor(0x70);
    print("Use the up and down arrow keys to scroll");
    int len = SCREEN_COLS - getCursorPosition();
    for (int i = 0; i < len; i++)
        putChar(' ');
    setColor(0x07);
}

extern "C" void shell() {
    char buff[65];

    printf("Which part of memory do you want to analyze?\nAddress: ");
    scan(buff, 10);
    unsigned int startAddr = ston<unsigned int>(buff);

    cls();
    DrawTopBar();

}