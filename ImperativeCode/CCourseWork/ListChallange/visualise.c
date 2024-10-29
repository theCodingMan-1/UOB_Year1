#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <limits.h>

long convertToNum(char number[]) {
    if (number[0] == '0' && number[1] != '\0') return -1; // no leading 0 -> "03" rejected

    char *endptr;
    long num = strtol(number, &endptr, 10);


    if (endptr == number) return -1;
    // this means no digits were found within the string (i.e "hello")

    else if (*endptr != '\0') return -1;
    // invalid character within the set (i.e "4y")
    // this is because the characters do not have null characters after them

    else return num;
}

char* convertToBin(long num, int power) {
    const int constantPower = power;
    int adder = 0;
    int q = 0;
    long r = abs(num);
    int memory = constantPower + (constantPower / 4) + 2;
    char output[memory];
    while (power > 0) {
        long divider = pow(2, power);
        q = r / divider;
        r = r % divider;
        char qStr[2];
            
        sprintf(qStr, "%d", q);
        output[constantPower - power + adder] = qStr[0];
        
            
        if (power % 4 == 0) {
            adder++;
            output[constantPower - power + adder] = ' ';

        }
        power--;
    }
    char rStr[2];
    sprintf(rStr, "%d", r);
    output[memory - 2] = rStr[0];

    if (num < 0) {
        int counter = memory - 2;
        int zero = 0;
        while (counter >= 0) {
            if ((output[counter] != ' ') && (zero == 1)) {

                if (output[counter] == '1') output[counter] = '0';
                else output[counter] = '1';
            }
            if (output[counter] == '1') zero = 1;
            counter--;
        }    
    }
    output[memory - 1] = '\0';
    return output;

}





char* character(char number[]) {
    long num;
    if ((number[0] == '-') && (number[1] == '1') && (number[2] == '\0')) {
        num = -1;
    }
    else {
        num = convertToNum(number);
        if (num == -1) return "Input Error";

        else if ((num < -128) || (num > 127)) return "Input Error";
    }

    int power = 7;

    return convertToBin(num, power);
}


char* integer(char number[]) {
    long num;
    if ((number[0] == '-') && (number[1] == '1') && (number[2] == '\0')) {
        num = -1;
    }
    else {
        num = convertToNum(number);
        if (num == -1) return "Input Error";

        else if ((num < -2147483648) || (num > 2147483647)) return "Input Error";
    }

    int power = 31;  
    
    return convertToBin(num, power);
}





char* unCharacter(char number[]) {

    long num = convertToNum(number);
    if (num == -1) return "Input Error";

    else if ((num < 0) || (num > 255)) return "Input Error";

    
    int power = 7;

    return convertToBin(num, power);
}



//---------------------TESTS----------------------------------------------------------------------



void assert(int line, bool b) {
    if (b) return;
    printf("The test on line %d fails.\n", line);
    exit(1);
}



void testCharacter(void) {
    assert(__LINE__, strcmp(character("-128"), "1000 0000") == 0);
    assert(__LINE__, strcmp(character("-104"), "1001 1000") == 0);
    assert(__LINE__, strcmp(character("43"), "0010 1011") == 0);
    assert(__LINE__, strcmp(character("127"), "0111 1111") == 0);
    assert(__LINE__, strcmp(character("-1"), "1111 1111") == 0);
    assert(__LINE__, strcmp(character("-129"), "Input Error") == 0);
    assert(__LINE__, strcmp(character("128"), "Input Error") == 0);
    assert(__LINE__, strcmp(character("4.5"), "Input Error") == 0);
    assert(__LINE__, strcmp(character("-0.65"), "Input Error") == 0);
    assert(__LINE__, strcmp(character("05"), "Input Error") == 0);
    assert(__LINE__, strcmp(character("4z"), "Input Error") == 0);
    assert(__LINE__, strcmp(character("4T3"), "Input Error") == 0);
    assert(__LINE__, strcmp(character("hello"), "Input Error") == 0);
}


void testInteger(void) {
    assert(__LINE__, strcmp(integer("-128"), "1000 0000") == 0);
    assert(__LINE__, strcmp(integer("-987654321"), "1100 0101 0010 0001 1001 0111 0100 1111") == 0);
    assert(__LINE__, strcmp(integer("1234567890"), "0100 1001 1001 0110 0000 0010 1101 0010") == 0);
    assert(__LINE__, strcmp(integer("127"), "0111 1111") == 0);
    assert(__LINE__, strcmp(integer("-1"), "1111 1111") == 0);
    assert(__LINE__, strcmp(integer("-129"), "Input Error") == 0);
    assert(__LINE__, integer("128") == "Input Error");
    assert(__LINE__, integer("4.5") == "Input Error");
    assert(__LINE__, integer("-0.65") == "Input Error");
    assert(__LINE__, integer("05") == "Input Error");
    assert(__LINE__, integer("4z") == "Input Error");
    assert(__LINE__, integer("4T3") == "Input Error");
    assert(__LINE__, integer("hello") == "Input Error");

}



void testUnCharacter(void){
    assert(__LINE__, strcmp(unCharacter("0"), "0000 0000") == 0);
    assert(__LINE__, strcmp(unCharacter("43"), "0010 1011") == 0);
    assert(__LINE__, strcmp(unCharacter("255"), "1111 1111") == 0);
    assert(__LINE__, strcmp(unCharacter("-1"), "Input Error") == 0);
    assert(__LINE__, strcmp(unCharacter("256"), "Input Error") == 0);
    assert(__LINE__, strcmp(unCharacter("4.5"), "Input Error") == 0);
    assert(__LINE__, strcmp(unCharacter("-0.65"), "Input Error") == 0);
    assert(__LINE__, strcmp(unCharacter("05"), "Input Error") == 0);
    assert(__LINE__, strcmp(unCharacter("4z"), "Input Error") == 0);
    assert(__LINE__, strcmp(unCharacter("4T3"), "Input Error") == 0);
    assert(__LINE__, strcmp(unCharacter("hello"), "Input Error") == 0);


}



void test(void) {
    testCharacter();
    testUnCharacter();
    printf("All Tests Pass!\n");
}



int main(int n, char *args[n]) {
    setbuf(stdout, NULL);
    if (n == 1) {
        test();
    }
    else if (n == 3) {
        if (strcmp(args[1], "char") == 0) printf("%s\n", character(args[2]));
        else if (strcmp(args[1], "int") == 0) printf("%s\n", integer(args[2]));
    }
    else if (n == 4) {
        if ((strcmp(args[1], "unsigned") == 0) && (strcmp(args[2], "char") == 0)){
            printf("%s\n", unCharacter(args[3]));
        }
        

    }
    else {
        printf("Use e.g.: ./visualise char 7\n");
    }
    return 0;
}
