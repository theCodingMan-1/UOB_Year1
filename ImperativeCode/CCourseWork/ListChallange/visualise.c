#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <limits.h>


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


}


char* character(char number[]) {
    // int num = convert(number);
    // printf("%d\n", num);
    if (number[0] == '0') return "Input Error"; // no leading 0 -> "03" rejected

    char *endptr;
    int num = strtol(number, &endptr, 10);


    if (endptr == number) return "Input Error";
    // this means no digits were found within the string (i.e "hello")

    else if (*endptr != '\0') return "Input Error";
    // invalid character within the set (i.e "4y")
    // this is because the characters do not have null characters after them

    else if ((num < 0) || (num > 255)) return "Input Error";

    else {
        int power = 7;
        int q = 0;
        int r = num;
        char output[11];
        while (power > 0) {
            int divider = pow(2, power);
            q = r / divider;
            r = r % divider;
            char qStr[10];
            sprintf(qStr, "%d", q);
            strcat(output, qStr);
            printf("%s\n", qStr);
            printf("%s\n\n", output);
            if (power == 4) strcat(output, " ");
            power--;
        }
        char rStr[11];
        sprintf(rStr, "%d", r);
        strcat(output, rStr);
        strcat(output, "\0");
        printf("%s\n", rStr);
        printf("%s\n\n", output);

        return output;
    }
}

void assert(int line, bool b) {
    if (b) return;
    printf("The test on line %d fails.\n", line);
    exit(1);
}



void testCharacter(void){
    assert(__LINE__, character("0") == "0000 0000");
    assert(__LINE__, character("43") == "Input Error");
    assert(__LINE__, character("255") == "1111 1111");
    assert(__LINE__, character("-1") == "Input Error");
    assert(__LINE__, character("256") == "Input Error");
    assert(__LINE__, character("4.5") == "Input Error");
    assert(__LINE__, character("-0.65") == "Input Error");
    assert(__LINE__, character("-1") == "Input Error");


}



void test(void) {
    testCharacter();
    printf("All Tests Pass!\n");
}



int main(int n, char *args[n]) {
    setbuf(stdout, NULL);
    if (n == 1) {
        test();
    }
    else if (n == 3) {
        if (strcmp(args[1], "char") == 0){
            // int num = character(args[2]);
            printf("%s\n", character(args[2]));
        }

        // if (a == char) printf("hey\n");
        // else printf("no\n");
        

    }
    else {
        printf("Use e.g.: ./visualise char 7\n");
    }
    return 0;
}
