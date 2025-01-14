/* Classify a triangle according to the integer lengths of its sides. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <limits.h>

// Integer constants representing types of triangle.
enum { Equilateral, Isosceles, Right, Scalene, Flat, Impossible, Illegal };

// Convert a string into an integer.  Return -1 if it is not valid.
int convert(const char length[]) {

    if (length[0] == '0') return -1; // no leading 0 -> "03" rejected

    char *endptr;
    int num = strtol(length, &endptr, 10);
    // length is the string to be converted
    // endptr used to store the pointer to the first character after the numeric value
    // 10 represents the base of the number system.

    if (endptr == length) return -1;
    // this means no digits were found within the string (i.e "hello")

    else if (*endptr != '\0') return -1;
    // invalid character within the set (i.e "4y")
    // this is because the characters do not have null characters after them

    else if (num <= 0) return -1;
    // if it is a negative number it returns -1
    // also if it is a number bigger than 214748367 it doesn't fit within the integers
    //      so it rolls over to the negatives which will return -1
    //      (i.e 214748367 + 1 = -214748368)

    else return num;


    // int num = atoi(length);
    // printf("%d\n", num);
    // if ((num > 2147483647) || (num <= 0)) return -1;
    // else return num;
}

int validate(int a, int b, int c) {
    if ((a <=0) || (b <= 0) || (c <= 0)) return -1;
    else return 1;
}

// Classify a triangle, given side lengths as strings:
int triangle(int a, int b, int c) {
    long al = a;
    long bl = b;
    long cl = c;
    if (validate(a, b, c) == 1){
        if ((a == b) && (b == c)) return Equilateral;

        else if ((a == b) || (b == c) || (c == a)) return Isosceles;

        else if ((al*al + bl*bl == cl*cl) || (al*al + cl*cl == bl*bl) || (bl*bl + cl*cl == al*al)) return Right;

        else if ((al + bl == cl) || (al + cl == bl) || (bl + cl == al)) return Flat;

        else if ((al > bl + cl) || (bl > al + cl) || (cl > al + bl)) return Impossible;

        else return Scalene;
    }
    else return Illegal;
}

// -----------------------------------------------------------------------------
// User interface and testing.

void print(int type) {
    switch (type) {
        case Equilateral: printf("Equilateral"); break;
        case Isosceles: printf("Isosceles"); break;
        case Right: printf("Right"); break;
        case Scalene: printf("Scalene"); break;
        case Flat: printf("Flat"); break;
        case Impossible: printf("Impossible"); break;
        case Illegal: printf("Illegal"); break;
    }
    printf("\n");
}

// A replacement for the library assert function.
void assert(int line, bool b) {
    if (b) return;
    printf("The test on line %d fails.\n", line);
    exit(1);
}

// Check that you haven't changed the triangle type constants.  (If you do, it
// spoils automatic marking, when your program is linked with a test program.)
void checkConstants(void) {
    assert(__LINE__, Equilateral==0 && Isosceles==1 && Right==2 && Scalene==3);
    assert(__LINE__, Flat==4 && Impossible==5 && Illegal==6);
}

// Tests 1 to 2: check equilateral
void testEquilateral(void) {
    assert(__LINE__, triangle(8, 8, 8) == Equilateral);
    assert(__LINE__, triangle(1073, 1073, 1073) == Equilateral);
}

// Tests 3 to 5: check isosceles
void testIsosceles(void) {
    assert(__LINE__, triangle(25, 25, 27) == Isosceles);
    assert(__LINE__, triangle(25, 27, 25) == Isosceles);
    assert(__LINE__, triangle(27, 25, 25) == Isosceles);
}

// Tests 6 to 14: check right angled
void testRight(void) {
    assert(__LINE__, triangle(3, 4, 5) == Right);
    assert(__LINE__, triangle(3, 5, 4) == Right);
    assert(__LINE__, triangle(5, 3, 4) == Right);
    assert(__LINE__, triangle(5, 12, 13) == Right);
    assert(__LINE__, triangle(5, 13, 12) == Right);
    assert(__LINE__, triangle(12, 5, 13) == Right);
    assert(__LINE__, triangle(12, 13, 5) == Right);
    assert(__LINE__, triangle(13, 5, 12) == Right);
    assert(__LINE__, triangle(13, 12, 5) == Right);
}

// Tests 15 to 20: check scalene
void testScalene(void) {
    assert(__LINE__, triangle(12, 14, 15) == Scalene);
    assert(__LINE__, triangle(12, 15, 14) == Scalene);
    assert(__LINE__, triangle(14, 12, 15) == Scalene);
    assert(__LINE__, triangle(14, 15, 12) == Scalene);
    assert(__LINE__, triangle(15, 12, 14) == Scalene);
    assert(__LINE__, triangle(15, 14, 12) == Scalene);
}

// Tests 21 to 25: check flat
void testFlat(void) {
    assert(__LINE__, triangle(7, 9, 16) == Flat);
    assert(__LINE__, triangle(7, 16, 9) == Flat);
    assert(__LINE__, triangle(9, 16, 7) == Flat);
    assert(__LINE__, triangle(16, 7, 9) == Flat);
    assert(__LINE__, triangle(16, 9, 7) == Flat);
}

// Tests 26 to 31: check impossible
void testImpossible(void) {
    assert(__LINE__, triangle(2, 3, 13) == Impossible);
    assert(__LINE__, triangle(2, 13, 3) == Impossible);
    assert(__LINE__, triangle(3, 2, 13) == Impossible);
    assert(__LINE__, triangle(3, 13, 2) == Impossible);
    assert(__LINE__, triangle(13, 2, 3) == Impossible);
    assert(__LINE__, triangle(13, 3, 2) == Impossible);
}

// Tests 32 to 44: check conversion.
// Leading zeros are disallowed because thy might be mistaken for octal.
void testConvert(void) {
    assert(__LINE__, convert("1") == 1);
    assert(__LINE__, convert("12345678") == 12345678);
    assert(__LINE__, convert("2147483647") == 2147483647);
    assert(__LINE__, convert("2147483648") == -1);
    assert(__LINE__, convert("2147483649") == -1);
    assert(__LINE__, convert("0") == -1);
    assert(__LINE__, convert("-1") == -1);
    assert(__LINE__, convert("-2") == -1);
    assert(__LINE__, convert("-2147483648") == -1);
    assert(__LINE__, convert("x") == -1);
    assert(__LINE__, convert("4y") == -1);
    assert(__LINE__, convert("13.4") == -1);
    assert(__LINE__, convert("03") == -1);
}

// Tests 45 to 50: check for correct handling of overflow
void testOverflow(void) {
    assert(__LINE__, triangle(2147483647,2147483647,2147483646) == Isosceles);
    assert(__LINE__, triangle(2147483645,2147483646,2147483647) == Scalene);
    assert(__LINE__, triangle(2147483647,2147483647,2147483647) == Equilateral);
    assert(__LINE__, triangle(1100000000,1705032704,1805032704) == Scalene);
    assert(__LINE__, triangle(2000000001,2000000002,2000000003) == Scalene);
    assert(__LINE__, triangle(150000002,666666671,683333338) == Scalene);
}

// Run tests on the triangle function.
void test(void) {
    checkConstants();
    testEquilateral();
    testIsosceles();
    testRight();
    testScalene();
    testFlat();
    testImpossible();
    testConvert();
    testOverflow();
    printf("All tests passed\n");
}

// Run the program or, if there are no arguments, test it.
int main(int n, char *args[n]) {
    setbuf(stdout, NULL);
    if (n == 1) {
        test();
    }
    else if (n == 4) {
        int a = convert(args[1]), b = convert(args[2]), c = convert(args[3]);
        int result = triangle(a, b, c);
        print(result);
    }
    else {
        fprintf(stderr, "Use e.g.: ./triangle 3 4 5\n");
        exit(1);
    }
    return 0;
}
