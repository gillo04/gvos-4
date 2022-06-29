#include "int.hpp"

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