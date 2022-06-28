#include "./lib/stdio.hpp"

extern "C" void shell() {
    char n1Str[10], n2Str[10];
    char buff[33] = {0};

    print("Input/output interrupts and library example\n\nInsert a number: ");
    scan(n1Str, 10);
    print("\nInsert another number: ");
    scan(n2Str, 10);
    
    print("\nThe sum of the numbers is ");
    print(utos(
        stou(n1Str) + stou(n2Str),
        10,
        buff
    ));
}