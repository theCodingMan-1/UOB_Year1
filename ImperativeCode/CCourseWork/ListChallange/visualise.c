#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <limits.h>



char* character(char number[]) {
    // int num = convert(number);
    // printf("%d\n", num);
    if (number[0] == '0' && number[1] != '\0') return "Input Error"; // no leading 0 -> "03" rejected

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
        char output[10];
        while (power > 0) {
            int divider = pow(2, power);
            q = r / divider;
            r = r % divider;
            char qStr[2];
            
            sprintf(qStr, "%d", q);
            if (power >= 4) output[7 - power] = qStr[0];
            else output[8 - power] = qStr[0];
            
            if (power == 4) output[4] = ' ';
            power--;
        }
        char rStr[2];
        sprintf(rStr, "%d", r);
        output[8] = rStr[0];
        output[9] = '\0';

        return output;
    }
}

void assert(int line, bool b) {
    if (b) return;
    printf("The test on line %d fails.\n", line);
    exit(1);
}



void testCharacter(void){
    assert(__LINE__, strcmp(character("0"), "0000 0000") == 0);
    assert(__LINE__, strcmp(character("43"), "0010 1011") == 0);
    assert(__LINE__, strcmp(character("255"), "1111 1111") == 0);
    assert(__LINE__, character("-1") == "Input Error");
    assert(__LINE__, character("256") == "Input Error");
    assert(__LINE__, character("4.5") == "Input Error");
    assert(__LINE__, character("-0.65") == "Input Error");
    assert(__LINE__, character("-1") == "Input Error");
    assert(__LINE__, character("05") == "Input Error");
    assert(__LINE__, character("4z") == "Input Error");
    assert(__LINE__, character("4T3") == "Input Error");
    assert(__LINE__, character("hello") == "Input Error");


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
