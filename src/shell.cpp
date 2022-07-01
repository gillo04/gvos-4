#include "./lib/stdio.hpp"



extern "C" void shell() {
    char n1Str[10], n2Str[10];
    char buff[33] = {0};

    print("Stdio.hpp functions example\n\n");

    print("\nInsert a number: ");
    scan(n1Str, 10);
    print("\nInsert another number: ");
    scan(n2Str, 10);
    
    print("\nThe sum of the numbers is ");
    print(ntos(
        ston<int>(n1Str) + ston<int>(n2Str),
        10,
        buff
    ));
}