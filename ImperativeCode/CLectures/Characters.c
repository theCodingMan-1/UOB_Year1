#include <stdio.h>
#include <string.h>

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

    char textB[8] = " there!"; // automatically splits it up
    printf("%s%s\n", textA, textB); // prints "Hi there!"

    char text[] = {'H', 'i', '\0'};
    // '\0' represents the null character and 
    // basically tells the program to stop when going through the list
    
}

// char is just a small integer where for instance 'A' is a synonym for the number 65,
// since 65 is the ASCII value of the character 'A'.
// Note '0' is a synonym for 48 not 0

// To define characters as ASCII symbols we use a backslash \ to define them. 
// '\0' is not 48 but the NULL character, which has the ASCII value of 0.


