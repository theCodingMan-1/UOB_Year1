/* Calculate a grade from a mark. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <assert.h>

// Integer constants representing grades.
enum { G1, G21, G22, G3, Fail, Invalid };

bool validate(int n, const char mark[]) {

    if (n >= 4 || n <= 0) return false;

    else {
        if (n == 1) {
            if (mark[0] - '0' <= 9 && mark[0] - '0' >= 0) { 
                // if the digit is between 0 - 9 then it passes the validation, e.g 4
                return true;
            }
            else return false;
        }
        else if (n == 2) {
            if (mark[0] - '0' <= 9 && mark[0] - '0' >= 0 && mark[1] - '0' <= 9 && mark[1] - '0' >= 0) {
                // if both digits are between 0 - 9 then is passes the validation, e.g 29
                return true;
            }
            else return false;

        }
        else if (n == 3) {
            if (mark[0] - '0' == 1 &&  mark[1] - '0' == 0  && mark[2] - '0' == 0) {
                // the only three digit number that works is if it equals 100, 
                // so the first digit must equal 1 and the second and third must equal 0
                // to pass the validation.
                return true;
            }
            else return false;
        }
    }

}



// Convert a mark string into an integer.  Return -1 if it is not valid.
// The argument n is the length of the string (normally 1 or 2 or 3).
int convert(int n, const char mark[]) {
    
    if (validate(n, mark) == true) { // only converts if the mark is a valid number

    /*
    mark[0] - '0' gets the ASCII value of the number represented by the character mark[0],
    (mark[0] will be anywhere from '0' to '9', which gives it an ASCII value between 48 and 57)
    and takes the ASCII value of the character '0' away from it. 
    This gives the ASCII value that will be somewhere between 0 - 9,
    which is equal to the character represented in mark[0].
    */
        switch (n) {
            case 1: return mark[0] - '0'; break; 

            case 2: {
                int tens = (mark[0] - '0') * 10;
                int digit = mark[1] - '0';
                return tens + digit;
            }
            break;

            case 3: {
                int hundred = (mark[0] - '0') * 100;
                int tens = (mark[1] - '0') * 10;
                int digit = mark[2] - '0';
                return hundred + tens + digit;
            }
            break;

            default: return -1;
        }
    }
    else {
        return -1;
    }
    
    
}

// Convert a mark integer into a grade.
int grade(int m) {
    if (m < 0 || m > 100) return Invalid;
    else if (70 <= m && m <= 100) return G1;
    else if (m >= 60) return G21;
    else if (m >= 50) return G22;
    else if (m >= 40) return G3;
    else return Fail;
}

// -----------------------------------------------------------------------------
// User interface and testing.

// Print out a grade.
void print(int grade) {
    if (grade == G1) printf("First\n");
    else if (grade == G21) printf("Upper second\n");
    else if (grade == G22) printf("Lower second\n");
    else if (grade == G3) printf("Third\n");
    else if (grade == Fail) printf("Fail\n");
    else if (grade == Invalid) printf("Invalid mark\n");
}

// Check that you haven't changed the grade constants.  (If you do, it spoils
// automatic marking, when your program is linked with a test program.)
void checkConstants() {
    assert(G1==0 && G21==1 && G22==2 && G3==3 && Fail==4 && Invalid==5);
}

// Test grade, at all the boundary points (tests 1 to 12)
void testGrade() {
    assert(grade(0) == Fail);
    assert(grade(39) == Fail);
    assert(grade(40) == G3);
    assert(grade(49) == G3);
    assert(grade(50) == G22);
    assert(grade(59) == G22);
    assert(grade(60) == G21);
    assert(grade(69) == G21);
    assert(grade(70) == G1);
    assert(grade(100) == G1);
    assert(grade(-1) == Invalid);
    assert(grade(101) == Invalid);
}

// Test convert on mark strings from "0" to "100" (tests 13 to 17).
void testConvert() {
    assert(convert(1, "0") == 0);
    assert(convert(1, "9") == 9);
    assert(convert(2, "10") == 10);
    assert(convert(2, "99") == 99);
    assert(convert(3, "100") == 100);
}

// Test that convert rejects non-digits, numbers outside the range 0..100, and
// unnecessary leading zeros which might cause ambiguity because they sometimes
// indicate octal (tests 18 to 25)
void testValidity() {
    assert(convert(4, "40.5") == -1);
    assert(convert(1, "x") == -1);
    assert(convert(2, "-1") == -1);
    assert(convert(4, "40x5") == -1);
    assert(convert(3, " 40") == -1);
    assert(convert(3, "101") == -1);
    assert(convert(3, "547") == -1);
    assert(convert(3, "040") == -1);
}

// Run the tests.
void test() {
    checkConstants();
    testGrade();
    testConvert();
    testValidity();
    printf("All tests pass\n");
}

// Deal with input and output. If there are no arguments call test. If there is
// one argument, calculate and print the grade.
int main(int n, char *args[n]) {
    setbuf(stdout, NULL);
    if (n == 1) test();
    else if (n == 2) print(grade(convert(strlen(args[1]), args[1])));
    else {
        fprintf(stderr, "Usage:   ./grade   or   ./grade m\n");
        fprintf(stderr, "where m is an integer mark from 0 to 100\n");
        return 1;
    }
    return 0;
}
