#include <stdio.h>

int main() {
    
    // Coercion -> when different types are combined without casts there are implicit rules of conversion. 
    //              There is an automatic conversion. 

    // During assignment if the number on the right is bigger than what the type can hold, 
    // the extra leftmost bits are truncated (lost)

    short word1 = 65536; // (0001)  0000 0000 0000 -> truncated
    short word2 = 65535; //         1111 1111 1111 -> fits ok



    // Masking -> used to mask a set of bits.

    unsigned char a = 0x9E; // holds    1001 1110
    unsigned char b = 0xF0; // holds    1111 0000
    unsigned char c = (a & b); // gives 1001 0000

    int n = 0;

    if ((n & 0x1) == 0x1) { // test for an odd number
        return 0;
    }


}

