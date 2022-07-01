#include "int.hpp"

// Number to string
// The possible bases range from binary to hex, not adbove
template <class T>
const char* ntos(T num, unsigned char base, char* str) {
    if (base < 2 || base > 16)
        return str;

    // Handle negative numbers
    int i = 0;
    bool negative = num < 0;
    if (negative){
        num = -num;
        str[0] = '-';
        i++;
    }

    // Encode
    do {
        str[i] = (num % base < 10) ? num % base + '0' : num % base + 'A' - 10;
        num /= base;
        i++;
    } while (num != 0);

    // Terminate string
    str[i] = 0;

    // Reverse string
    for (int j = 0; j < i/2; j++) {
        int neg = (negative) ? 1 : 0;
        char tmp = str[j + neg];
        str[j + neg] = str[i-1-j];
        str[i-1-j] = tmp;
    }
    
    return str;
}

// String to number
// Only handles base 10 for now
template<class T>
T ston(const char* str) {
    T num = 0;
    bool negative = str[0] == '-';

    // Reach the end of the string
    int i = 0;
    while (str[i] != 0)
        i ++;

    // Decode
    int pow = 1;
    for (i--; i >= (negative) ? 1 : 0; i--){
        num += (str[i] - '0') * pow;
        pow *= 10;
    }

    // Handle negative numbers
    if (negative)
        num = -num;

    return num;
}

// Printf-like function
// Use *%d* for integers, *%u* for unsigned integers, *%c* for chars
void printf(const char* format) {
    print(format);
}

template<typename T, typename... Targs>
void printf(const char* format, T value, Targs... Fargs) {
    while (*format != '\0') {
        if (*format == '%') {
            format++;
            char buff[65];
            switch (*format) {
            case 'd':
                ntos((signed)value, 10, buff);
                print(buff);
                break;
            case 'u':
                ntos((unsigned)value, 10, buff);
                print(buff);
                break;
            case 'c':
                putChar(value);
                break;
            }
            printf(format + 1, Fargs...); // recursive call
            return;
        }
        putChar(*format);
        format++;
    }
}