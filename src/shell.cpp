#include "./lib/stdio.hpp"

extern "C" void shell() {
    char buff[65];

    printf("Which part of memory do you want to analyze?\nAddress: ");
    scan(buff, 10);
    unsigned int startAddr = ston<unsigned int>(buff);

    cls();
    DrawTopBar();

}

void DrawTopBar(){
    
}