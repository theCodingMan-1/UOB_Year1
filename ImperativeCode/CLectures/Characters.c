#include <stdio.h>

int character(void) {
    char c = 65;
    printf("%hhi\n", c); // prints out the number "65"

    printf("%c %hhi\n", c, c); // prints out "A 65"
    // this is because 65 is the decimal ASCII value for A
}

int string(void) {
    char textA[3] = {72, 105, 0};
    printf("%s\n", textA); // prints out "Hi"
    // This is because 75 is the decimal ASCII for "H"
    // and 105 is the decimal ASCII for "i"
    // and 0 is the decimal ASCII for the null character
    // string needs to be terminated by null at the end

    char textB[8] = " there!" // automatically splits it up
    printf("%s%s\n", textA, textB) // prints "Hi there!"
}